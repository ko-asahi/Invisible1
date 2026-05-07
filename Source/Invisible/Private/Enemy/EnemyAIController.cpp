// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAIController.h"
#include "Enemy/EnemyBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MotionWarpingComponent.h"
#include "DrawDebugHelpers.h"
#include "BrainComponent.h" 
#include "InvisibleGameStateBase.h"
#include "Player/PlayerCharacter.h"
#include "Perception/AISense_Hearing.h"
#include "Enemy/Interaction/AIBehaviorDialogueSubsystem.h"
#include "Engine/GameInstance.h"
#include "Invisible_GameModeBase.h"
#include "Components/SceneComponent.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

// Blackboard 键名定义
const FName AEnemyAIController::BB_TargetActor      = TEXT("TargetActor");
const FName AEnemyAIController::BB_WaypointBehavior = TEXT("WaypointBehavior");
const FName AEnemyAIController::BB_WaypointWaitTime = TEXT("WaypointWaitTime");
const FName AEnemyAIController::BB_LookAngle        = TEXT("LookAngle");
const FName AEnemyAIController::BB_LookSpeed        = TEXT("LookSpeed");
const FName AEnemyAIController::BB_HeardLocation   = TEXT("HeardLocation");
const FName AEnemyAIController::BB_IsInvestigating = TEXT("IsInvestigating");
const FName AEnemyAIController::BB_Alertness        = TEXT("Alertness");
const FName AEnemyAIController::BB_HasVisualContact = TEXT("HasVisualContact");
const FName AEnemyAIController::BB_IsSuspicious     = TEXT("IsSuspicious");
const FName AEnemyAIController::BB_IsChasing        = TEXT("IsChasing");
const FName AEnemyAIController::BB_LastSeenLocation = TEXT("LastSeenLocation");
const FName AEnemyAIController::BB_VisualTargetActor = TEXT("VisualTargetActor");
const FName AEnemyAIController::BB_UseLookCenterYaw = TEXT("UseLookCenterYaw");
const FName AEnemyAIController::BB_LookCenterYaw = TEXT("LookCenterYaw");
const FName AEnemyAIController::BB_PreLookPauseTime = TEXT("PreLookPauseTime");
const FName AEnemyAIController::BB_InterestLocation = TEXT("InterestLocation");
const FName AEnemyAIController::BB_HasInterest = TEXT("HasInterest");
const FName AEnemyAIController::BB_IsFiring = TEXT("IsFiring");


AEnemyAIController::AEnemyAIController()
{
    // 启用 Tick
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;

    // 创建感知组件
    PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
    SetPerceptionComponent(*PerceptionComp);

    // 创建听觉配置
    HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
    HearingConfig->HearingRange = HearingRange; // 听觉半径
    HearingConfig->SetMaxAge(HearingMaxAge); // 丢失刺激后的保留时间
    HearingConfig->bUseLoSHearing = bUseLoSHearing; // 是否需要视线才“听到”
    HearingConfig->DetectionByAffiliation.bDetectEnemies   = true;
    HearingConfig->DetectionByAffiliation.bDetectNeutrals  = true;
    HearingConfig->DetectionByAffiliation.bDetectFriendlies= true;

    // 必须先 ConfigureSense 把配置注册到组件，SetSenseEnabled 才能找到对应的 SenseConfig
    PerceptionComp->ConfigureSense(*HearingConfig);
    PerceptionComp->SetDominantSense(HearingConfig->GetSenseImplementation());
    PerceptionComp->SetSenseEnabled(UAISense_Hearing::StaticClass(), bEnableHearing);

    // OnTargetPerceptionUpdated 直接传入 FAIStimulus，不需要再调 GetActorsPerception，更可靠
    PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetPerceptionUpdated);
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (bInjectedPathTurnInProgress)
    {
        if (AEnemyBase* SelfEnemy = Cast<AEnemyBase>(GetPawn()))
        {
            RotateActorToward(SelfEnemy, InjectedPathFirstGoal, DeltaSeconds);
        }
    }

    // 等待阶段：目标AI原地持续朝向“预计互动点”
    if (bExternalApproachHold)
    {
        if (AEnemyBase* SelfEnemy = Cast<AEnemyBase>(GetPawn()))
        {
            if (bExternalHoldUseFaceLocation)   // 源AI走向目标AI时，目标AI朝向预计互动点
            {
                RotateActorToward(SelfEnemy, ExternalHoldFaceLocation, DeltaSeconds);
            }
            else if (AActor* FaceActor = ExternalHoldFaceActor.Get())   // 源AI走到目标AI触发距离时，进行修正
            {
                RotateActorToward(SelfEnemy, FaceActor->GetActorLocation(), DeltaSeconds);
            }
        }
    }

    if(!bIsRunningPendingInteraction)
    {
        return;
    }

    AEnemyBase* SelfEnemy = Cast<AEnemyBase>(GetPawn());
    AActor* TargetActor = PendingInteractionContext.TargetActor.Get();

    if(!SelfEnemy || !TargetActor)
    {
        return;
    }

    ApplyInteractionFacing(SelfEnemy, TargetActor, DeltaSeconds);
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    AEnemyBase* Enemy = Cast<AEnemyBase>(InPawn);
    if(!Enemy) return;

    // Tag 回退：若蓝图中未配置，自动尝试项目默认值（false=缺失时不报错）
    if (!SleepActionTag.IsValid())
    {
        SleepActionTag = FGameplayTag::RequestGameplayTag(FName("Behavior.AI.Interact.Sleep"), false);
    }
    if (!SitActionTag.IsValid())
    {
        SitActionTag = FGameplayTag::RequestGameplayTag(FName("Behavior.AI.Interact.Sit"), false);
    }

    // 获取互动时转向速度
    InteractionTurnSpeed = FMath::Max(Enemy->InteractionTurnSpeed, 0.0f);
    InjectedPathTurnAnim = Enemy->InjectedPathTurnAnim;
    InjectedPathTurnSplitNormalizedTime = FMath::Clamp(Enemy->InjectedPathTurnSplitNormalizedTime, 0.05f, 0.95f);
    InjectedPathTurnMinAngle = FMath::Max(Enemy->InjectedPathTurnMinAngle, 0.0f);
    InjectedPathTurnPlayRate = FMath::Max(Enemy->InjectedPathTurnPlayRate, 0.1f);
    InjectedPathTurnMaxWaitTime = FMath::Max(Enemy->InjectedPathTurnMaxWaitTime, 0.1f);

    // 从敌人类获取感知参数
    SightRadius = Enemy->SightRadius;
    HalfViewAngle = Enemy->HalfViewAngle;

    // 从敌人类获取警戒配置
    const FEnemyAlertConfig& Cfg = Enemy->AlertConfig;
    MaxAlertness        = Cfg.MaxAlertness;
    NearRange           = Cfg.NearRange;
    MidRange            = Cfg.MidRange;
    FarRange            = Cfg.FarRange;
    NearGainRate        = Cfg.NearGainRate;
    MidGainRate         = Cfg.MidGainRate;
    FarGainRate         = Cfg.FarGainRate;
    AlertDecayRate      = Cfg.AlertDecayRate;
    SuspiciousThreshold = Cfg.SuspiciousThreshold;
    ChaseThreshold      = Cfg.ChaseThreshold;
    LoseTargetThreshold = Cfg.LoseTargetThreshold;
    InvestigateLookDuration = Cfg.InvestigateLookDuration;
    HearingAlertGain        = Cfg.HearingAlertGain;
    StandGainMultiplier = Cfg.StandGainMultiplier;
    WalkGainMultiplier = Cfg.WalkGainMultiplier;
    RunGainMultiplier = Cfg.RunGainMultiplier;
    CrouchIdleGainMultiplier = Cfg.CrouchIdleGainMultiplier;
    CrouchWalkGainMultiplier = Cfg.CrouchWalkGainMultiplier;
    // PreLookPauseTime    = Cfg.PreLookPauseTime;

    // 同步斗殴运动扭曲配置
    bEnableBrawlMotionWarping = Enemy->bEnableBrawlMotionWarping;
    BrawlBehaviorRootTag = Enemy->BrawlBehaviorRootTag;
    BrawlWarpTargetName = Enemy->BrawlWarpTargetName.IsNone() ? FName(TEXT("BrawlTarget")) : Enemy->BrawlWarpTargetName;
    BrawlHalfSpacing = FMath::Max(10.0f, Enemy->BrawlHalfSpacing);

    if(Enemy && Enemy->BehaviorTree)
    {
        // 运行行为树
        RunBehaviorTree(Enemy->BehaviorTree);
    }

    // 启动定时视野检测函数
    // GetWorldTimerManager().SetTimer(
    //     DetectionTimerHandle, this,
    //     &AEnemyAIController::TickDetection,
    //     0.1f, true);
    StartDetectionTimer();

    // 初始化视觉警戒相关黑板值
    if(UBlackboardComponent* BB = GetBlackboardComponent())
    {
        BB->SetValueAsBool(BB_HasInterest, false);
        BB->SetValueAsBool(BB_IsInvestigating, false);
        BB->SetValueAsBool(BB_IsChasing, false);
    }

    // ===== 听觉检测全局变量应用 =====
    // 确保运行时参数（尤其是蓝图覆盖值）写回到感知配置
    HearingConfig->HearingRange = HearingRange;
    HearingConfig->SetMaxAge(HearingMaxAge);
    HearingConfig->bUseLoSHearing = bUseLoSHearing;
    HearingConfig->DetectionByAffiliation.bDetectEnemies   = true;
    HearingConfig->DetectionByAffiliation.bDetectNeutrals  = true;
    HearingConfig->DetectionByAffiliation.bDetectFriendlies= true;
    PerceptionComp->ConfigureSense(*HearingConfig);
    PerceptionComp->SetSenseEnabled(UAISense_Hearing::StaticClass(), bEnableHearing);
    PerceptionComp->SetDominantSense(HearingConfig->GetSenseImplementation());

    // 从游戏状态获取听觉范围（初始化时调用）
    ApplyHearingRangeFromGameState();
    PerceptionComp->RequestStimuliListenerUpdate();

    UE_LOG(LogTemp, Log, TEXT("[AI] Hearing Init: Enabled=%d Range=%.1f MaxAge=%.2f UseLOS=%d"),
        (int32)bEnableHearing, HearingRange, HearingMaxAge, (int32)bUseLoSHearing);

    // 绑定全局听觉范围变化的回调（热更新时调用）
    if (AInvisibleGameStateBase* GS = GetWorld()->GetGameState<AInvisibleGameStateBase>())
    {
        if (!GS->OnGlobalHearingRangeChanged.IsAlreadyBound(this, &AEnemyAIController::HandleGlobalHearingRangeChanged))
        {
            GS->OnGlobalHearingRangeChanged.AddDynamic(this, &AEnemyAIController::HandleGlobalHearingRangeChanged);
        }
    }

    // 初始化状态标签
    InitAIStateTags();

    Enemy->SetAIStateTag(Tag_AI_Idle);
}

// 停止定时视野检测
void AEnemyAIController::OnUnPossess()
{
    if (AInvisibleGameStateBase* GS = GetWorld()->GetGameState<AInvisibleGameStateBase>())
    {
        GS->OnGlobalHearingRangeChanged.RemoveDynamic(this, &AEnemyAIController::HandleGlobalHearingRangeChanged);
    }

    GetWorldTimerManager().ClearTimer(DetectionTimerHandle);
    GetWorldTimerManager().ClearTimer(PendingInteractionTimerHandle);
    GetWorldTimerManager().ClearTimer(InteractionFacingTimerHandle);
    GetWorldTimerManager().ClearTimer(InjectedPathTurnTimerHandle);
    ResetInjectedPathTurnState();
    StopDialogueRefreshLoop();
    ClearDialogueBubbleDelayTimers();
    ClearSpecialObjectInteractionRuntimeFlags();
    Super::OnUnPossess();
}

// 定时视野检测计时器
void AEnemyAIController::StartDetectionTimer()
{
    // 检测频率不能小于0.02秒，防止出现bug
    if(DetectionInterval < 0.02f)
    {
        DetectionInterval = 0.02f;
    }

    GetWorldTimerManager().ClearTimer(DetectionTimerHandle);
    GetWorldTimerManager().SetTimer(
        DetectionTimerHandle,
        this,
        &AEnemyAIController::TickDetection,
        DetectionInterval,
        true
    );

    UE_LOG(LogTemp, Log, TEXT("视觉检测计时器启动，频率: %f秒"), DetectionInterval);
}

// 提交最后看到或者听到的位置
void AEnemyAIController::CommitInterestLocation(const FVector& Location)
{
    UBlackboardComponent* BB = GetBlackboardComponent();

    
    if (!BB) return;

    BB->SetValueAsVector(BB_InterestLocation, Location);
    BB->SetValueAsVector(BB_LastSeenLocation, Location);    // 更新最后看到的位置，兼容现有FaceTarget（将废弃）逻辑
    BB->SetValueAsBool(BB_HasInterest, true);
    BB->SetValueAsBool(BB_IsInvestigating, false);   // 先看向目标点
}

// 暂停视觉机制
void AEnemyAIController::SetAIPaused(bool bPaused)
{
    bIsAIPaused = bPaused;

    if(bIsAIPaused)
    {
        StopMovement();
        GetWorldTimerManager().ClearTimer(DetectionTimerHandle);
        GetWorldTimerManager().ClearTimer(InjectedPathTurnTimerHandle);
        ResetInjectedPathTurnState();

        if(UBrainComponent* Brain = GetBrainComponent())
        {
            Brain->StopLogic(TEXT("编辑模式暂停"));
        }

        // 暂停时若有残留绑定，先解绑，防止重复回调
        if(GetPathFollowingComponent() && InjectedPathFinishedHandle.IsValid())
        {
            GetPathFollowingComponent()->OnRequestFinished.Remove(InjectedPathFinishedHandle);
            InjectedPathFinishedHandle.Reset();
            UE_LOG(LogTemp, Log, TEXT("解绑插入路径完成回调"));
        }

        UE_LOG(LogTemp, Log, TEXT("视觉检测暂停"));
    }
    else
    {
        // if(UBrainComponent* Brain = GetBrainComponent())
        // {
        //     Brain->RestartLogic();
        // }
        // 处于外部等待锁：不走InjectedPath，也不恢复巡逻
        if (bExternalApproachHold)
        {
            StartDetectionTimer();
            StopMovement();

            // 立刻停下，防止滑步
            if (UCharacterMovementComponent* MoveComp = GetPawn() ? GetPawn()->FindComponentByClass<UCharacterMovementComponent>() : nullptr)
            {
                MoveComp->StopMovementImmediately();
            }

            if (UBrainComponent* Brain = GetBrainComponent())
            {
                Brain->StopLogic(TEXT("外部等待生效"));
            }
            UE_LOG(LogTemp, Log, TEXT("AI恢复：外部等待锁生效，保持原地等待"));
            return;
        }

        StartDetectionTimer();

        // 有插入路径时，先走插入路径
        if(HasValidInjectedPath())
        {
            StartInjectedPath();
            UE_LOG(LogTemp, Log, TEXT("AI恢复,执行编辑路径"));
        }
        else
        {
            if (UBrainComponent* Brain = GetBrainComponent())
            {
                Brain->RestartLogic();
            }
            UE_LOG(LogTemp, Log, TEXT("AI恢复,执行巡逻行为树"));
        }

        UE_LOG(LogTemp, Log, TEXT("视觉检测恢复"));
    }
}

// 按距离获取增长速率
float AEnemyAIController::GetAlertGainRateByDistance(float Distance) const
{
    // 默认 Near <= Mid <= Far
    if (Distance <= NearRange) return NearGainRate;
    if (Distance <= MidRange)  return MidGainRate;
    if (Distance <= FarRange)  return FarGainRate;
    return 0.f;
}


// 获取玩家状态并得出最终警戒值增长倍率
float AEnemyAIController::GetPlayerStateAlertMultiplier(const APlayerCharacter* Player) const
{
    if(!Player) return 1.0f;

    const FGameplayTag RunTag        = FGameplayTag::RequestGameplayTag(FName("State.Movement.Run"));
    const FGameplayTag WalkTag       = FGameplayTag::RequestGameplayTag(FName("State.Movement.Walk"));
    const FGameplayTag CrouchWalkTag = FGameplayTag::RequestGameplayTag(FName("State.Movement.CrouchWalk"));
    const FGameplayTag CrouchIdleTag = FGameplayTag::RequestGameplayTag(FName("State.Movement.CrouchIdle"));
    const FGameplayTag IdleTag       = FGameplayTag::RequestGameplayTag(FName("State.Movement.Idle"));

    const FGameplayTagContainer& PlayerTags = Player->MovementStateTags;

    if(PlayerTags.HasTagExact(CrouchWalkTag)) return CrouchWalkGainMultiplier;
    if(PlayerTags.HasTagExact(CrouchIdleTag)) return CrouchIdleGainMultiplier;
    if(PlayerTags.HasTagExact(RunTag)) return RunGainMultiplier;
    if(PlayerTags.HasTagExact(WalkTag)) return WalkGainMultiplier;
    if(PlayerTags.HasTagExact(IdleTag)) return StandGainMultiplier;

    return 1.0f;
}

// 定时检测玩家是否在视野范围内
void AEnemyAIController::TickDetection()
{
    if(bIsAIPaused) return;

    UBlackboardComponent* BB = GetBlackboardComponent();
    if (!BB) return;

    if (bInteractionDisableAllSenses)
    {
        BB->SetValueAsFloat(BB_Alertness, Alertness);
        BB->SetValueAsBool(BB_HasVisualContact, false);
        BB->SetValueAsBool(BB_IsSuspicious, false);
        BB->SetValueAsBool(BB_IsChasing, false);
        BB->SetValueAsBool(BB_HasInterest, false);
        BB->SetValueAsBool(BB_IsInvestigating, false);
        BB->ClearValue(BB_VisualTargetActor);
        return;
    }

    const float NowTime = GetWorld()->GetTimeSeconds();
    const float Dt = FMath::Max(DetectionInterval, KINDA_SMALL_NUMBER);

    // ===== 刺激检测 =====
    float Distance = 0.f;
    const bool bInSight = IsPlayerInFanSight(Distance);
    const bool bHeardValid = bHasHeardStimulus && (NowTime - LastHeardGameTime <= HearingMaxAge);
    const bool bHasAnyStimulus = bInSight || bHeardValid;
    APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    const float PlayerStateMultiplier = GetPlayerStateAlertMultiplier(Player);

    // ===== 警戒值更新 =====
    if (bInSight)
        Alertness += GetAlertGainRateByDistance(Distance) * PlayerStateMultiplier * Dt;
    else if (bHeardValid)
        Alertness += (HearingAlertGain / FMath::Max(HearingMaxAge, 0.1f)) * Dt;
    else
        Alertness -= AlertDecayRate * Dt;

    Alertness = FMath::Clamp(Alertness, 0.f, MaxAlertness);
    const bool bChasing = (Alertness >= ChaseThreshold);
    const bool bAlertFull = MaxAlertness > KINDA_SMALL_NUMBER && Alertness >= MaxAlertness - KINDA_SMALL_NUMBER;
    if(bAlertFull)
    {
        if(AInvisible_GameModeBase* GameMode = Cast<AInvisible_GameModeBase>(UGameplayStatics::GetGameMode(this)))
        {
            if(!GameMode->IsGameOverStarted())
            {
                if(AEnemyBase* Enemy = Cast<AEnemyBase>(GetPawn()))
                {
                    EnterGameOverFire(Player);
                    GameMode->BeginGameOver(Enemy);
                    UE_LOG(LogTemp, Log, TEXT("[AI] 警戒值满，进入游戏结束开火状态"));
                }
            }
        }
        return;
    }

    if (bInterruptInteractionOnChase && bIsRunningPendingInteraction && bChasing)
    {
        UE_LOG(LogTemp, Log, TEXT("[AI] 达到打探阈值，中断当前互动并切回打探行为"));
        InterruptPendingInteractionForAlert();
    }

    // ===== 黑板基础值 =====
    BB->SetValueAsFloat(BB_Alertness, Alertness);
    BB->SetValueAsBool(BB_HasVisualContact, bInSight);
    BB->SetValueAsBool(BB_IsSuspicious, false);
    BB->SetValueAsBool(BB_IsChasing, bChasing);
    BB->ClearValue(BB_VisualTargetActor);

    // ===== 位置记录 =====
    if (bInSight && !bWasInSightLastTick && Player)
    {
        FirstSeenLocation = Player->GetActorLocation();
        bVisualFirstLock = true;
    }
    if (bInSight && Player)
        BB->SetValueAsVector(BB_LastSeenLocation, Player->GetActorLocation());
    if (!bInSight && bWasInSightLastTick)
        bVisualFirstLock = false;

    // ===== 兴趣状态激活（视觉/听觉统一入口） =====
    // 仅当 HasInterest 从 false 变 true 时触发，确保所有任务阶段均可被打断
    const bool bPrevHasInterest = BB->GetValueAsBool(BB_HasInterest);
    if (bChasing && bInteractionSuppressInterestUntilChase)
    {
        bInteractionSuppressInterestUntilChase = false;
        UE_LOG(LogTemp, Log, TEXT("[AI] 坐下互动已达到打探阈值，解除兴趣抑制"));
    }

    const bool bSuppressInterestForSit = bInteractionSuppressInterestUntilChase && !bChasing;
    if (bHasAnyStimulus && !bPrevHasInterest && !bSuppressInterestForSit)
    {
        FVector InterestLoc = FVector::ZeroVector;
        if (bInSight && Player)
        {
            // 若 FirstSeenLocation 被清理过（如打探结束后），回退到玩家当前位置
            if (FirstSeenLocation.IsNearlyZero())
                FirstSeenLocation = Player->GetActorLocation();
            InterestLoc = FirstSeenLocation;
        }
        else if (bHeardValid)
            InterestLoc = LastHeardLocation;

        BB->SetValueAsVector(BB_InterestLocation, InterestLoc);
        if (bInSight && Player)
            BB->SetValueAsVector(BB_LastSeenLocation, InterestLoc);
        BB->SetValueAsBool(BB_HasInterest, true);
        BB->SetValueAsBool(BB_IsInvestigating, true);
        InterestHoldUntilTime = NowTime + FMath::Max(InvestigateLookDuration, 0.5f);

        // 立刻停止物理移动
        if (APawn* ControlledPawn = GetPawn())
            if (UCharacterMovementComponent* MC = ControlledPawn->FindComponentByClass<UCharacterMovementComponent>())
                MC->StopMovementImmediately();
        StopMovement();

        UE_LOG(LogTemp, Log, TEXT("[AI] 兴趣激活: 视野=%d 听觉=%d 目标=%s Alertness=%.1f"),
            (int)bInSight, (int)bHeardValid, *InterestLoc.ToString(), Alertness);
    }

    // ===== 看向阶段超时兜底 =====
    // 若 FaceTarget 任务未及时运行，超时后自动解锁 IsInvestigating
    bool bIsCurrentlyFacing = BB->GetValueAsBool(BB_IsInvestigating);
    if (bIsCurrentlyFacing && NowTime >= InterestHoldUntilTime)
    {
        BB->SetValueAsBool(BB_IsInvestigating, false);
        bIsCurrentlyFacing = false;
        UE_LOG(LogTemp, Warning, TEXT("[AI] 看向阶段超时，强制解锁 IsInvestigating"));
    }

    // ===== 追击阈值优先：已到追击阈值时强制中断看向阶段 =====
    // 这样不需要等看向超时，Alertness 一到 ChaseThreshold 就立刻进入移动阶段
    if (bChasing && bIsCurrentlyFacing)
    {
        BB->SetValueAsBool(BB_IsInvestigating, false);
        bIsCurrentlyFacing = false;
        UE_LOG(LogTemp, Warning, TEXT("[AI] 达到追击阈值，强制中断看向阶段，切入移动"));
    }

    // ===== 打探阈值后更新移动目标（仅在看向阶段结束后执行） =====
    if (bChasing && !bIsCurrentlyFacing && BB->GetValueAsBool(BB_HasInterest))
    {
        FVector MoveTarget = FVector::ZeroVector;
        bool bHasMoveTarget = false;

        if (bInSight && Player)
        {
            MoveTarget = Player->GetActorLocation();
            bHasMoveTarget = true;
        }
        else if (bHeardValid)
        {
            MoveTarget = LastHeardLocation;
            bHasMoveTarget = true;
        }
        else
        {
            MoveTarget = BB->GetValueAsVector(BB_LastSeenLocation);
            bHasMoveTarget = !MoveTarget.IsNearlyZero();
        }

        if (bHasMoveTarget)
        {
            BB->SetValueAsVector(BB_InterestLocation, MoveTarget);
            BB->SetValueAsBool(BB_HasInterest, true);
        }
    }

    // ===== 过期清理听觉缓存 =====
    if (!bHeardValid && bHasHeardStimulus)
    {
        bHasHeardStimulus = false;
        LastHeardLocation = FVector::ZeroVector;
        LastHeardGameTime = -1.0f;
        BB->ClearValue(BB_HeardLocation);
    }

    // ===== 无刺激时自动清除兴趣状态 =====
    const bool bIsInvestigating = BB->GetValueAsBool(BB_IsInvestigating);
    if (!bHasAnyStimulus && !bIsInvestigating && Alertness <= LoseTargetThreshold && NowTime >= InterestHoldUntilTime)
    {
        if (BB->GetValueAsBool(BB_HasInterest))
        {
            BB->SetValueAsBool(BB_HasInterest, false);
            UE_LOG(LogTemp, Log, TEXT("[AI] 无刺激，兴趣状态清除"));
        }
    }

    bWasInSightLastTick = bInSight;

    // 每帧同步AI状态Tag
    UpdateAIStateTags();

    // ===== 调试日志：实时打印打探相关状态 =====
    if (AEnemyBase* Enemy = Cast<AEnemyBase>(GetPawn()))
    {
        const bool bDbgHasInterest = BB->GetValueAsBool(BB_HasInterest);
        const bool bDbgIsInvestigating = BB->GetValueAsBool(BB_IsInvestigating);
        const bool bDbgIsChasing = BB->GetValueAsBool(BB_IsChasing);
        const float DbgAlertness = BB->GetValueAsFloat(BB_Alertness);
        const FString DbgAIStateTag = Enemy->AIStateTags.IsEmpty() ? TEXT("None") : Enemy->AIStateTags.ToStringSimple();

        // UE_LOG(
        //     LogTemp,
        //     Warning,
        //     TEXT("[AI Debug][%s] HasInterest=%d IsInvestigating=%d IsChasing=%d Alertness=%.2f AIStateTag=%s"),
        //     *GetNameSafe(Enemy),
        //     (int32)bDbgHasInterest,
        //     (int32)bDbgIsInvestigating,
        //     (int32)bDbgIsChasing,
        //     DbgAlertness,
        //     *DbgAIStateTag
        // );
    }
}

// 判断玩家是否在视野范围内
bool AEnemyAIController::IsPlayerInFanSight(float& OutDistance) const
{
    OutDistance = 0.0f;

    APawn* EnemyPawn = GetPawn();
    if (!EnemyPawn) return false;

    ACharacter* Player = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if(!Player) return false;

    FVector EnemyLoc = EnemyPawn->GetActorLocation();
    FVector PlayerLoc = Player->GetActorLocation();

    // XY平面上距离
    FVector2D EnemyPos2D (EnemyLoc.X,  EnemyLoc.Y);
    FVector2D PlayerPos2D(PlayerLoc.X, PlayerLoc.Y);
    FVector2D ToPlayer2D = PlayerPos2D - EnemyPos2D;
    
    float Distance = ToPlayer2D.Size();
    OutDistance = Distance;

    // 获取最远可见范围
    const float MaxSight = FMath::Min(SightRadius, FarRange);
    if (Distance > MaxSight) return false;

   



    // 角度检测
    FVector2D Forward2D(EnemyPawn->GetActorForwardVector().X,EnemyPawn->GetActorForwardVector().Y);
    Forward2D.Normalize();

    FVector2D ToPlayerDir = ToPlayer2D.GetSafeNormal();
    float DotProduct = FVector2D::DotProduct(Forward2D, ToPlayerDir);
    float CosHalfAngle = FMath::Cos(FMath::DegreesToRadians(HalfViewAngle));

    if(DotProduct < CosHalfAngle) return false;



    // 射线检测是否存在障碍物
    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(EnemyPawn);
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, EnemyLoc, PlayerLoc, ECC_Visibility, Params);
    if (bHit && HitResult.GetActor() != Player) return false;



    // 开发模式下可视化
#if ENABLE_DRAW_DEBUG
    FVector Forward3D = EnemyPawn->GetActorForwardVector();
    float AngleRad = FMath::DegreesToRadians(HalfViewAngle);
    FVector LeftDir  = Forward3D.RotateAngleAxis( HalfViewAngle, FVector::UpVector);
    FVector RightDir = Forward3D.RotateAngleAxis(-HalfViewAngle, FVector::UpVector);
    DrawDebugLine(GetWorld(), EnemyLoc, EnemyLoc + LeftDir  * SightRadius, FColor::Green, false, 0.15f);
    DrawDebugLine(GetWorld(), EnemyLoc, EnemyLoc + RightDir * SightRadius, FColor::Green, false, 0.15f);
#endif


    return true;
}



// ===== 听觉检测 =====
// OnTargetPerceptionUpdated 直接提供 FAIStimulus，无需再调 GetActorsPerception 中间层
// 提前触发 TickDetection 以实现即时响应（不等待下一个 0.1s 周期）
void AEnemyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if (bInteractionDisableAllSenses)
    {
        return;
    }

    if (Stimulus.Type != UAISense::GetSenseID<UAISense_Hearing>()) return;
    if (!Stimulus.WasSuccessfullySensed()) return;

    LastHeardLocation = Stimulus.StimulusLocation;
    bHasHeardStimulus = true;
    LastHeardGameTime = GetWorld()->GetTimeSeconds();

    if (UBlackboardComponent* BB = GetBlackboardComponent())
        BB->SetValueAsVector(BB_HeardLocation, LastHeardLocation);

    // 即时触发一次检测，确保听觉响应不延迟到下一个 TickDetection 周期
    TickDetection();

    UE_LOG(LogTemp, Log, TEXT("[AI] 听到声音: 位置=%s 强度=%.2f"), *LastHeardLocation.ToString(), Stimulus.Strength);
}
// 从游戏状态获取听觉范围
void AEnemyAIController::ApplyHearingRangeFromGameState()
{
    if(!HearingConfig || !PerceptionComp) return;

    if(AInvisibleGameStateBase* GS = GetWorld()->GetGameState<AInvisibleGameStateBase>())
    {
        HearingRange = GS->GetGlobalHearingRange();    // 缓存听觉范围
        HearingConfig->HearingRange = HearingRange;    // 更新听觉配置
        PerceptionComp->RequestStimuliListenerUpdate();    // 立即刷新感知监听器
        UE_LOG(LogTemp, Log, TEXT("从游戏状态获取听觉范围: %f"), HearingRange);
    }
}

// 处理全局听觉范围变化的回调
void AEnemyAIController::HandleGlobalHearingRangeChanged(float NewRange)
{
    if(!HearingConfig || !PerceptionComp) return;

    HearingRange = NewRange;
    HearingConfig->HearingRange = HearingRange;
    PerceptionComp->RequestStimuliListenerUpdate();
    UE_LOG(LogTemp, Log, TEXT("全局听觉范围变化: %f"), HearingRange);
}

// ===== 编辑模式插入路径 =====
// 检查路径是否有效
bool AEnemyAIController::HasValidInjectedPath() const
{
    return InjectedPathPoints.Num() >= 2;
}

// 设置编辑模式绘制后的临时路径
void AEnemyAIController::SetInjectedPath(const TArray<FVector>& InPathPoints)
{
    InjectedPathPoints = InPathPoints;
    InjectedPathIndex = INDEX_NONE;

    if(!HasValidInjectedPath())
    {
        InjectedPathIndex = INDEX_NONE;
        UE_LOG(LogTemp, Log, TEXT("SetInjectedPath失败: 路径点不足"));
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("SetInjectedPath成功: 路径点数量: %d"), InjectedPathPoints.Num());
}

// 开始插入路径
void AEnemyAIController::StartInjectedPath()
{
    if (!HasValidInjectedPath())
    {
        FinishInjectedPathAndResumePatrol();
        return;
    }

    UPathFollowingComponent* PathComp = GetPathFollowingComponent();
    if (!PathComp)
    {
        FinishInjectedPathAndResumePatrol();
        return;
    }

    // 执行插入路径时先停BT，防止并发MoveTo
    if (UBrainComponent* Brain = GetBrainComponent())
    {
        Brain->StopLogic(TEXT("执行插入路径"));
    }

    if (InjectedPathFinishedHandle.IsValid())
    {
        PathComp->OnRequestFinished.Remove(InjectedPathFinishedHandle);
        InjectedPathFinishedHandle.Reset();
    }

    InjectedPathFinishedHandle = PathComp->OnRequestFinished.AddUObject(
        this, &AEnemyAIController::HandleInjectedPathMoveFinished);

    // PathPoints[0]通常是当前点，从1开始移动
    InjectedPathIndex = 1;
    BeginInjectedPathTurnThenMove();
}

bool AEnemyAIController::ShouldPlayInjectedPathTurn(AEnemyBase* SelfEnemy, const FVector& Goal, float& OutDeltaYaw) const
{
    OutDeltaYaw = 0.0f;
    if (!SelfEnemy)
    {
        return false;
    }

    const FVector ToGoal = (Goal - SelfEnemy->GetActorLocation()).GetSafeNormal2D();
    if (ToGoal.IsNearlyZero())
    {
        return false;
    }

    const float TargetYaw = ToGoal.Rotation().Yaw;
    OutDeltaYaw = FMath::FindDeltaAngleDegrees(SelfEnemy->GetActorRotation().Yaw, TargetYaw);
    return FMath::Abs(OutDeltaYaw) >= InjectedPathTurnMinAngle;
}

float AEnemyAIController::PlayInjectedPathTurnAnimation(AEnemyBase* SelfEnemy, float DeltaYaw)
{
    if (!SelfEnemy || !InjectedPathTurnAnim)
    {
        return 0.0f;
    }

    USkeletalMeshComponent* MeshComp = SelfEnemy->GetMesh();
    if (!MeshComp)
    {
        return 0.0f;
    }

    UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
    if (!AnimInstance)
    {
        return 0.0f;
    }

    UAnimMontage* DynamicMontage = UAnimMontage::CreateSlotAnimationAsDynamicMontage(
        InjectedPathTurnAnim,
        FName(TEXT("DefaultSlot")),
        0.1f,
        0.1f,
        InjectedPathTurnPlayRate,
        1);

    if (!DynamicMontage)
    {
        return 0.0f;
    }

    InjectedPathTurnDynamicMontage = DynamicMontage;

    const float ClipLength = FMath::Max(InjectedPathTurnAnim->GetPlayLength(), KINDA_SMALL_NUMBER);
    const float SplitTime = FMath::Clamp(InjectedPathTurnSplitNormalizedTime, 0.05f, 0.95f) * ClipLength;
    // UE中 FindDeltaAngleDegrees 正值通常代表向左转，这里按“右转=前半段”映射为负值。
    const bool bTurnRight = DeltaYaw < 0.0f;
    const float StartTime = bTurnRight ? 0.0f : SplitTime;
    const float SegmentLength = bTurnRight ? SplitTime : (ClipLength - SplitTime);
    const float SafeSegmentLength = FMath::Max(SegmentLength / FMath::Max(InjectedPathTurnPlayRate, KINDA_SMALL_NUMBER), 0.05f);

    const float PlayedLen = AnimInstance->Montage_Play(DynamicMontage, InjectedPathTurnPlayRate, EMontagePlayReturnType::MontageLength, StartTime);
    if (PlayedLen <= 0.0f)
    {
        InjectedPathTurnDynamicMontage = nullptr;
        return 0.0f;
    }

    return SafeSegmentLength;
}

void AEnemyAIController::ResetInjectedPathTurnState()
{
    bInjectedPathTurnInProgress = false;
    InjectedPathFirstGoal = FVector::ZeroVector;
    InjectedPathTurnDynamicMontage = nullptr;

    if (AEnemyBase* SelfEnemy = Cast<AEnemyBase>(GetPawn()))
    {
        if (UCharacterMovementComponent* MoveComp = SelfEnemy->GetCharacterMovement())
        {
            MoveComp->bOrientRotationToMovement = bInjectedPathSavedOrientRotationToMovement;
            MoveComp->RotationRate = InjectedPathSavedRotationRate;
        }
    }
}

void AEnemyAIController::BeginInjectedPathTurnThenMove()
{
    if (!InjectedPathPoints.IsValidIndex(InjectedPathIndex))
    {
        FinishInjectedPathAndResumePatrol();
        return;
    }

    AEnemyBase* SelfEnemy = Cast<AEnemyBase>(GetPawn());
    if (!SelfEnemy)
    {
        MoveToInjectedPoint(InjectedPathIndex);
        return;
    }

    InjectedPathFirstGoal = InjectedPathPoints[InjectedPathIndex];

    float DeltaYaw = 0.0f;
    if (!ShouldPlayInjectedPathTurn(SelfEnemy, InjectedPathFirstGoal, DeltaYaw))
    {
        MoveToInjectedPoint(InjectedPathIndex);
        return;
    }

    UCharacterMovementComponent* MoveComp = SelfEnemy->GetCharacterMovement();
    if (!MoveComp)
    {
        MoveToInjectedPoint(InjectedPathIndex);
        return;
    }

    bInjectedPathSavedOrientRotationToMovement = MoveComp->bOrientRotationToMovement;
    InjectedPathSavedRotationRate = MoveComp->RotationRate;
    MoveComp->bOrientRotationToMovement = false;
    MoveComp->RotationRate = FRotator(0.f, FMath::Max(InteractionTurnSpeed, 0.0f), 0.f);

    StopMovement();
    MoveComp->StopMovementImmediately();

    bInjectedPathTurnInProgress = true;

    const float PlayedDuration = PlayInjectedPathTurnAnimation(SelfEnemy, DeltaYaw);
    const float RotateDuration = FMath::Abs(DeltaYaw) / FMath::Max(InteractionTurnSpeed, 1.0f);
    float WaitDuration = FMath::Max(PlayedDuration, RotateDuration);
    if (PlayedDuration <= 0.0f)
    {
        WaitDuration = RotateDuration;
    }
    WaitDuration = FMath::Clamp(WaitDuration, 0.05f, InjectedPathTurnMaxWaitTime);

    GetWorldTimerManager().ClearTimer(InjectedPathTurnTimerHandle);
    GetWorldTimerManager().SetTimer(
        InjectedPathTurnTimerHandle,
        this,
        &AEnemyAIController::FinishInjectedPathTurnAndMove,
        WaitDuration,
        false);
}

void AEnemyAIController::FinishInjectedPathTurnAndMove()
{
    GetWorldTimerManager().ClearTimer(InjectedPathTurnTimerHandle);

    AEnemyBase* SelfEnemy = Cast<AEnemyBase>(GetPawn());
    if (SelfEnemy)
    {
        if (InjectedPathTurnDynamicMontage && SelfEnemy->GetMesh())
        {
            if (UAnimInstance* AnimInstance = SelfEnemy->GetMesh()->GetAnimInstance())
            {
                AnimInstance->Montage_Stop(0.05f, InjectedPathTurnDynamicMontage);
            }
        }

        const FVector ToGoal = (InjectedPathFirstGoal - SelfEnemy->GetActorLocation()).GetSafeNormal2D();
        if (!ToGoal.IsNearlyZero())
        {
            SelfEnemy->SetActorRotation(ToGoal.Rotation());
        }
    }

    ResetInjectedPathTurnState();
    MoveToInjectedPoint(InjectedPathIndex);
}

// 移动到插入路径点
void AEnemyAIController::MoveToInjectedPoint(int32 PointIndex)
{
    if (!InjectedPathPoints.IsValidIndex(PointIndex))
    {
        FinishInjectedPathAndResumePatrol();
        return;
    }

    const FVector Goal = InjectedPathPoints[PointIndex];
    float AcceptRadius = 30.0f;
    // 关键修复：交互路径的最后一点，不再用固定30，而用交互半径
    const bool bIsLastInjectedPoint = (PointIndex == InjectedPathPoints.Num() - 1);
    if (bIsLastInjectedPoint && HasValidPendingInteraction())
    {
        AcceptRadius = FMath::Max(30.0f, PendingInteractionExecutionRadius);
    }
    const EPathFollowingRequestResult::Type Req = MoveToLocation(Goal, AcceptRadius, false, true, true, false, nullptr, true);

    
    if (Req == EPathFollowingRequestResult::Failed)
    {
        UE_LOG(LogTemp, Warning, TEXT("插入路径 MoveTo 失败，索引: %d"), PointIndex);
        FinishInjectedPathAndResumePatrol();
    }
}


// 插入路径完成回调
void AEnemyAIController::HandleInjectedPathMoveFinished(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    if (Result.Code != EPathFollowingResult::Success)
    {
        UE_LOG(LogTemp, Warning, TEXT("插入路径中断/失败，结果码: %d"), (int32)Result.Code);
        FinishInjectedPathAndResumePatrol();
        return;
    }

    ++InjectedPathIndex;
    if (InjectedPathPoints.IsValidIndex(InjectedPathIndex))
    {
        MoveToInjectedPoint(InjectedPathIndex);
    }
    else
    {
        FinishInjectedPathAndResumePatrol();
    }
}


// 完成插入路径并恢复巡逻
void AEnemyAIController::FinishInjectedPathAndResumePatrol()
{
    GetWorldTimerManager().ClearTimer(InjectedPathTurnTimerHandle);
    ResetInjectedPathTurnState();

    if (UPathFollowingComponent* PathComp = GetPathFollowingComponent())
    {
        if (InjectedPathFinishedHandle.IsValid())
        {
            PathComp->OnRequestFinished.Remove(InjectedPathFinishedHandle);
            InjectedPathFinishedHandle.Reset();
        }
    }

    InjectedPathPoints.Reset();
    InjectedPathIndex = INDEX_NONE;

    // 若有待执行互动，优先进入互动，不立刻恢复巡逻
    if (HasValidPendingInteraction())
    {
        StartPendingInteraction();
        UE_LOG(LogTemp, Log, TEXT("插入路径结束，进入待执行互动行为"));
        return;
    }

    if (UBrainComponent* Brain = GetBrainComponent())
    {
        Brain->RestartLogic();
    }

    UE_LOG(LogTemp, Log, TEXT("插入路径结束，恢复巡逻行为树"));
}

// 延长兴趣状态最短保持时间，供 BT Task 在启动时注入自身持续时长
void AEnemyAIController::ExtendInterestHoldTime(float Duration)
{
    if (UWorld* World = GetWorld())
    {
        InterestHoldUntilTime = FMath::Max(InterestHoldUntilTime, World->GetTimeSeconds() + Duration);
    }
}

// MoveTo 后，清除运行时状态
void AEnemyAIController::ClearInvestigateRuntimeState(bool bClearHeardMemory)
{
    // 清理视觉锁相关
    bVisualFirstLock = false;
    //bWasInSightLastTick = false;
    FirstSeenLocation = FVector::ZeroVector;
    InterestHoldUntilTime = -1.0f;
    Alertness = 0.0f;

    // 可选清理听觉缓存
    if (bClearHeardMemory)
    {
        bHasHeardStimulus = false;
        LastHeardLocation = FVector::ZeroVector;
        LastHeardGameTime = -1.0f;
    }
}


// ===== 编辑模式互动执行（ai行为执行） =====
// 设置待执行互动
void AEnemyAIController::SetPendingInteractionContext(const FTraitInteractionContext& InContext)
{
    // PendingInteractionTarget = TargetActor;
    // PendingInteractionBehaviorTag = BehaviorTag;
    // PendingInteractionDuration = FMath::Max(0.0f, Duration);
    // PendingInteractionExecutionRadius = FMath::Max(0.0f, ExecutionRadius);
    // bHasPendingInteraction = TargetActor != nullptr;
    PendingInteractionContext = InContext;
    bHasPendingInteraction = PendingInteractionContext.IsValid();

    // 兼容旧逻辑
    PendingInteractionTarget = PendingInteractionContext.TargetActor.Get();
    PendingInteractionBehaviorTag = PendingInteractionContext.Spec.ActionTag;
    PendingInteractionDuration = FMath::Max(0.0f, PendingInteractionContext.Spec.Duration);
    PendingInteractionExecutionRadius = FMath::Max(0.0f, PendingInteractionContext.Spec.ExecutionRadius);
}

// 清除待执行互动
void AEnemyAIController::ClearPendingInteraction()
{
    // 先缓存目标控制器，避免后面清空上下文后拿不到
    AEnemyAIController* TargetCtrlToRelease = nullptr;
    if (AEnemyBase* PendingTargetEnemy = Cast<AEnemyBase>(PendingInteractionContext.TargetActor.Get()))
    {
        TargetCtrlToRelease = Cast<AEnemyAIController>(PendingTargetEnemy->GetController());
    }

    bHasPendingInteraction = false;
    bIsRunningPendingInteraction = false;

    PendingInteractionTarget.Reset();
    PendingInteractionBehaviorTag = FGameplayTag();
    PendingInteractionDuration = 0.0f;
    PendingInteractionExecutionRadius = 0.0f;
    PendingInteractionContext = FTraitInteractionContext(); // 清空上下文

    GetWorldTimerManager().ClearTimer(PendingInteractionTimerHandle);
    GetWorldTimerManager().ClearTimer(InteractionFacingTimerHandle);
    StopDialogueRefreshLoop();
    ClearDialogueBubbleDelayTimers();

    // 清理待执行互动完成回调
    if(UPathFollowingComponent* PathComp = GetPathFollowingComponent())
    {
        if(PendingInteractionApproachFinishedHandle.IsValid())
        {
            PathComp->OnRequestFinished.Remove(PendingInteractionApproachFinishedHandle);
            PendingInteractionApproachFinishedHandle.Reset();
        }
    }

    SetForcedInteractionStateTag(false, FGameplayTag());
    ClearSpecialObjectInteractionRuntimeFlags();

    // 释放目标等待锁，防止未开始互动就卡住
    if (TargetCtrlToRelease)
    {
        TargetCtrlToRelease->ClearExternalApproachHold();
    }
}

// 检查路径是否有效
bool AEnemyAIController::HasValidPendingInteraction() const
{
    return bHasPendingInteraction && PendingInteractionContext.IsValid();
}

// 接近目标（原逻辑：开始执行待执行互动，已废弃）
void AEnemyAIController::StartPendingInteraction()
{
    // // 路径无效时，清理待执行互动
    // if (!HasValidPendingInteraction())
    // {
    //     ClearPendingInteraction();
    //     if (UBrainComponent* Brain = GetBrainComponent())
    //     {
    //         Brain->RestartLogic();
    //     }
    //     return;
    // }

    // bIsRunningPendingInteraction = true;

    // // 互动期间停止移动，停止检测，避免状态机覆盖
    // StopMovement();
    // GetWorldTimerManager().ClearTimer(DetectionTimerHandle);

    // if (UBrainComponent* Brain = GetBrainComponent())
    // {
    //     Brain->StopLogic(TEXT("执行编辑模式互动行为"));
    // }

    // if (AEnemyBase* SelfEnemy = Cast<AEnemyBase>(GetPawn()))
    // {
    //     // 直接用行为Tag作为状态Tag，方便在蓝图里根据Tag切动画
    //     if (PendingInteractionBehaviorTag.IsValid())
    //     {
    //         SelfEnemy->SetAIStateTag(PendingInteractionBehaviorTag);
    //     }
    // }

    // BP_OnPendingInteractionStarted(PendingInteractionTarget.Get(), PendingInteractionBehaviorTag, PendingInteractionDuration);
    // // 设置计时器，确保互动时长不会因为AI状态机暂停而中断
    // const float SafeDuration = FMath::Max(PendingInteractionDuration, 0.1f);
    // GetWorldTimerManager().SetTimer(
    //     PendingInteractionTimerHandle,
    //     this,
    //     &AEnemyAIController::FinishPendingInteraction,
    //     SafeDuration,
    //     false
    // );

    if (!HasValidPendingInteraction() || !ValidatePendingInteractionContext(TEXT("StartPendingInteraction")))
    {
        ClearPendingInteraction();
        if (UBrainComponent* Brain = GetBrainComponent())
        {
            Brain->RestartLogic();
        }
        return;
    }

    bIsRunningPendingInteraction = true;

    // 停BT防并发MoveTo
    if (UBrainComponent* Brain = GetBrainComponent())
    {
        Brain->StopLogic(TEXT("执行互动-接近目标阶段"));
    }

    StartPendingInteractionApproach();
}

// 开始接近目标
void AEnemyAIController::StartPendingInteractionApproach()
{
    AActor* TargetActor = PendingInteractionContext.TargetActor.Get();
    if(!TargetActor)
    {
        FinishPendingInteraction();
        return;
    }

    UPathFollowingComponent* PathComp = GetPathFollowingComponent();
    if(!PathComp)
    {
        FinishPendingInteraction();
        return;
    }

    if(PendingInteractionApproachFinishedHandle.IsValid())
    {
        PathComp->OnRequestFinished.Remove(PendingInteractionApproachFinishedHandle);
        PendingInteractionApproachFinishedHandle.Reset();
    }

    PendingInteractionApproachFinishedHandle = PathComp->OnRequestFinished.AddUObject(
        this, &AEnemyAIController::HandlePendingInteractionApproachFinished);

    const float AcceptRadius = FMath::Max(10.0f, PendingInteractionContext.Spec.ExecutionRadius);
    const EPathFollowingRequestResult::Type Req = MoveToActor(
        TargetActor,
        AcceptRadius,
        true,
        true,
        true,
        nullptr,
        true
    );

    if(Req == EPathFollowingRequestResult::Failed)
    {
        FinishPendingInteraction();
    }
}

// 接近目标完成回调
void AEnemyAIController::HandlePendingInteractionApproachFinished(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    if (UPathFollowingComponent* PathComp = GetPathFollowingComponent())
    {
        if (PendingInteractionApproachFinishedHandle.IsValid())
        {
            PathComp->OnRequestFinished.Remove(PendingInteractionApproachFinishedHandle);
            PendingInteractionApproachFinishedHandle.Reset();
        }
    }

    if (Result.Code != EPathFollowingResult::Success)
    {
        FinishPendingInteraction();
        return;
    }

    BeginPendingInteractionLoop();

}

// 开始执行待执行互动循环
void AEnemyAIController::BeginPendingInteractionLoop()
{
    AActor* TargetActor = PendingInteractionContext.TargetActor.Get();
    AEnemyBase* SelfEnemy = Cast<AEnemyBase>(GetPawn());

    // 清除目标AI的外部等待锁
    if (AEnemyBase* TargetEnemy = Cast<AEnemyBase>(TargetActor))
    {
        if (AEnemyAIController* TargetCtrl = Cast<AEnemyAIController>(TargetEnemy->GetController()))
        {
            TargetCtrl->ClearExternalApproachHold();
        }
    }

    if(!TargetActor || !SelfEnemy)
    {
        FinishPendingInteraction();
        return;
    }

    // 获取互动行为Tag
    const FGameplayTag ActionTag = PendingInteractionContext.Spec.ActionTag;
    if(!ActionTag.IsValid())
    {
        FinishPendingInteraction();
        return;
    }
    const bool bIsChatLike = IsChatLikeInteraction(ActionTag);

    SnapToObjectInteractionAnchor(SelfEnemy, TargetActor, ActionTag);
    ApplySpecialObjectInteractionRuntimeFlags(SelfEnemy, ActionTag);

    // 互动期间停止移动，但不关闭检测
    StopMovement();

    ApplyInteractionFacing(SelfEnemy, TargetActor, GetWorld()->GetDeltaSeconds());
    ApplyInteractionStateLock(SelfEnemy, TargetActor, ActionTag, bIsChatLike);

    // 应用斗殴运动扭曲
    ApplyBrawlMotionWarping(SelfEnemy, TargetActor, ActionTag);


    // 互动开始时尝试显示头顶文本
    TryShowInteractionDialogueBubble(SelfEnemy, TargetActor, ActionTag, bIsChatLike);
    // 可选：启用对话自动刷新（默认关闭，不影响原有逻辑）
    if (bEnableDialogueAutoRefresh)
    {
        StartDialogueRefreshLoop(SelfEnemy, TargetActor, ActionTag, bIsChatLike);
    }

    // // 源ai 切为互动Tag
    // if(PendingInteractionContext.Spec.ActionTag.IsValid())
    // {
    //     SelfEnemy->SetAIStateTag(PendingInteractionContext.Spec.ActionTag);
    // }

    // // 如果目标也是敌人，可同步目标Tag并让其朝向自己
    // if (AEnemyBase* TargetEnemy = Cast<AEnemyBase>(TargetActor))
    // {
    //     // 同步目标Tag
    //     if (PendingInteractionContext.Spec.ActionTag.IsValid())
    //     {
    //         TargetEnemy->SetAIStateTag(PendingInteractionContext.Spec.ActionTag);
    //     }

    //     // 朝向自己
    //     const FVector ToSource = (SelfEnemy->GetActorLocation() - TargetEnemy->GetActorLocation()).GetSafeNormal2D();
    //     if (!ToSource.IsNearlyZero())
    //     {
    //         TargetEnemy->SetActorRotation(ToSource.Rotation());
    //     }
    // }

    GetWorldTimerManager().ClearTimer(InteractionFacingTimerHandle);

    // const float FacingTickInterval = 0.016f; 
    // GetWorldTimerManager().SetTimer(
    //     InteractionFacingTimerHandle,
    //     this,
    //     &AEnemyAIController::TickInteractionFacing,
    //     FacingTickInterval,   // 约60Hz，想省性能可用0.033f
    //     true
    // );

    BP_OnPendingInteractionStarted(TargetActor, PendingInteractionContext.Spec.ActionTag, PendingInteractionContext.Spec.Duration);

    // 开始事件计时
    const float SafeDuration = FMath::Max(PendingInteractionContext.Spec.Duration, 0.1f);
    GetWorldTimerManager().SetTimer(
        PendingInteractionTimerHandle,
        this,
        &AEnemyAIController::FinishPendingInteraction,
        SafeDuration,
        false
    );
}


// 完成执行待执行互动
void AEnemyAIController::FinishPendingInteraction()
{
    AActor* TargetActor = PendingInteractionTarget.Get();
    const FGameplayTag BehaviorTag = PendingInteractionBehaviorTag;

    BP_OnPendingInteractionFinished(TargetActor, BehaviorTag);

    // 在特殊情况下清除目标AI的外部等待锁
    if (AEnemyBase* TargetEnemy = Cast<AEnemyBase>(PendingInteractionContext.TargetActor.Get()))
    {
        if (AEnemyAIController* TargetCtrl = Cast<AEnemyAIController>(TargetEnemy->GetController()))
        {
            TargetCtrl->ClearExternalApproachHold();
        }
    }

    // 先释放目标AI锁
    if(ActiveInteractionTargetController.IsValid())
    {
        ActiveInteractionTargetController->SetForcedInteractionStateTag(false, FGameplayTag());
        ActiveInteractionTargetController.Reset();
    }

    // 广播事件结束信息
    AActor* SourceActor = PendingInteractionContext.SourceActor.Get();
    AActor* TargetActorForEvent = PendingInteractionContext.TargetActor.Get();
    const FGameplayTag ActionTagForEvent = PendingInteractionContext.Spec.ActionTag;
    OnInteractionResolvedNative.Broadcast(
        SourceActor,
        TargetActorForEvent,
        ActionTagForEvent,
        EInteractionEndReason::Completed
    );

    // 释放自身（源AI）锁，清理上下文
    SetForcedInteractionStateTag(false, FGameplayTag());
    ClearSpecialObjectInteractionRuntimeFlags();
    StopDialogueRefreshLoop();
    ClearPendingInteraction();
    GetWorldTimerManager().ClearTimer(InteractionFacingTimerHandle);

    // 清理并隐藏头顶文本
    AEnemyBase* SelfEnemy = Cast<AEnemyBase>(GetPawn());
    ClearDialogueBubbleDelayTimers();
    HideInteractionDialogueBubble(SelfEnemy, TargetActor);

    // 完成互动，恢复常规巡逻ai
    if (!GetWorldTimerManager().IsTimerActive(DetectionTimerHandle))
    {
        StartDetectionTimer();
    }
    if(UBrainComponent* Brain = GetBrainComponent())
    {
        Brain->RestartLogic();
    }
    UE_LOG(LogTemp, Log, TEXT("编辑模式互动完成，恢复常规巡逻ai"));
}

// 中断当前待执行互动
void AEnemyAIController::InterruptPendingInteractionForAlert()
{
    if (!bIsRunningPendingInteraction)
    {
        return;
    }

    AActor* TargetActor = PendingInteractionTarget.Get();
    const FGameplayTag BehaviorTag = PendingInteractionBehaviorTag;

    // 清除互动计时器，避免后续又触发“正常结束”
    GetWorldTimerManager().ClearTimer(PendingInteractionTimerHandle);
    GetWorldTimerManager().ClearTimer(InteractionFacingTimerHandle);

    // 通知蓝图“被中断”
    BP_OnPendingInteractionInterrupted(TargetActor, BehaviorTag);

    // 在特殊情况下清除目标AI的外部等待锁
    if (AEnemyBase* TargetEnemy = Cast<AEnemyBase>(PendingInteractionContext.TargetActor.Get()))
    {
        if (AEnemyAIController* TargetCtrl = Cast<AEnemyAIController>(TargetEnemy->GetController()))
        {
            TargetCtrl->ClearExternalApproachHold();
        }
    }

    // 中断时也进行释放
    if (ActiveInteractionTargetController.IsValid())
    {
        ActiveInteractionTargetController->SetForcedInteractionStateTag(false, FGameplayTag());
        ActiveInteractionTargetController.Reset();
    }

    // 广播事件结束信息
    AActor* SourceActor = PendingInteractionContext.SourceActor.Get();
    AActor* TargetActorForEvent = PendingInteractionContext.TargetActor.Get();
    const FGameplayTag ActionTagForEvent = PendingInteractionContext.Spec.ActionTag;
    OnInteractionResolvedNative.Broadcast(
        SourceActor,
        TargetActorForEvent,
        ActionTagForEvent,
        EInteractionEndReason::Interrupted
    );

    // 释放自身（源AI）锁，清理上下文
    SetForcedInteractionStateTag(false, FGameplayTag());
    ClearSpecialObjectInteractionRuntimeFlags();
    StopDialogueRefreshLoop();
    // 清理互动运行态（会把 bIsRunningPendingInteraction 置 false）
    ClearPendingInteraction();

    // 清理并隐藏头顶文本
    AEnemyBase* SelfEnemy = Cast<AEnemyBase>(GetPawn());
    ClearDialogueBubbleDelayTimers();
    HideInteractionDialogueBubble(SelfEnemy, TargetActor);

    // 保证感知检测在运行
    if (!GetWorldTimerManager().IsTimerActive(DetectionTimerHandle))
    {
        StartDetectionTimer();
    }

    // 重启BT，让AI立即进入打探分支
    if (UBrainComponent* Brain = GetBrainComponent())
    {
        Brain->RestartLogic();
    }
}


// 强制状态 Tag （用于在互动期间防止被常规状态机覆盖）
void AEnemyAIController::SetForcedInteractionStateTag(bool bEnable, FGameplayTag InTag)
{
    bUseForcedInteractionStateTag = bEnable && InTag.IsValid();
    ForcedInteractionStateTag = bUseForcedInteractionStateTag ? InTag : FGameplayTag();

    if(AEnemyBase* Enemy = Cast<AEnemyBase>(GetPawn()))
    {
        if(bUseForcedInteractionStateTag)
        {
            Enemy->SetAIStateTag(ForcedInteractionStateTag);
        }
    }
}

// ai转向函数
void AEnemyAIController::RotateActorToward(AActor* ActorToRotate, const FVector& TargetLocation, float DeltaSeconds) const
{
    if(!ActorToRotate) return;

    const FVector ToTarget = (TargetLocation - ActorToRotate->GetActorLocation()).GetSafeNormal2D();
    if(ToTarget.IsNearlyZero()) return;

    const FRotator CurrentRot = ActorToRotate->GetActorRotation();
    const FRotator TargetRot = ToTarget.Rotation();
    const FRotator NewRot = FMath::RInterpConstantTo(
        CurrentRot,
        TargetRot,
        DeltaSeconds,
        InteractionTurnSpeed   // 度/秒
    );

    ActorToRotate->SetActorRotation(NewRot);
}

// 互动时转向计时器回调
void AEnemyAIController::TickInteractionFacing()
{
    if(!bIsRunningPendingInteraction)
    {
        GetWorldTimerManager().ClearTimer(InteractionFacingTimerHandle);
        return;
    }

    AEnemyBase* SelfEnemy = Cast<AEnemyBase>(GetPawn());
    AActor* TargetActor = PendingInteractionContext.TargetActor.Get();

    if(!SelfEnemy || !TargetActor)
    {
        GetWorldTimerManager().ClearTimer(InteractionFacingTimerHandle);
        return;
    }

    ApplyInteractionFacing(SelfEnemy, TargetActor, GetWorld()->GetDeltaSeconds());
    
}


// ===== 外部等待锁（用于“目标AI原地等待”）=====

// 目标朝向A走到的预估位置
void AEnemyAIController::SetExternalApproachHoldByLocation(const FVector& InFaceLocation)
{
    GetWorldTimerManager().ClearTimer(InjectedPathTurnTimerHandle);
    ResetInjectedPathTurnState();

    bExternalApproachHold = true;
    bExternalHoldUseFaceLocation = true;
    ExternalHoldFaceLocation = InFaceLocation;
    ExternalHoldFaceActor.Reset();

    // 保持原地
    StopMovement();
    if (UCharacterMovementComponent* MoveComp = GetPawn() ? GetPawn()->FindComponentByClass<UCharacterMovementComponent>() : nullptr)
    {
        MoveComp->StopMovementImmediately();
    }

    // 关键：清空注入路径，避免恢复后继续走导致追逐
    InjectedPathPoints.Reset();
    InjectedPathIndex = INDEX_NONE;

    // 停BT，防止其它任务驱动移动
    if (UBrainComponent* Brain = GetBrainComponent())
    {
        Brain->StopLogic(TEXT("目标朝向A走到的预估位置"));
    }
}

// 目标朝向最终修正到A走到的位置
void AEnemyAIController::SetExternalApproachHoldByActor(AActor* InFaceActor)
{
    GetWorldTimerManager().ClearTimer(InjectedPathTurnTimerHandle);
    ResetInjectedPathTurnState();

    bExternalApproachHold = true;
    bExternalHoldUseFaceLocation = false;
    ExternalHoldFaceActor = InFaceActor;

    StopMovement();
    if (UCharacterMovementComponent* MoveComp = GetPawn() ? GetPawn()->FindComponentByClass<UCharacterMovementComponent>() : nullptr)
    {
        MoveComp->StopMovementImmediately();
    }
    
    InjectedPathPoints.Reset();
    InjectedPathIndex = INDEX_NONE;

    if (UBrainComponent* Brain = GetBrainComponent())
    {
        Brain->StopLogic(TEXT("ExternalApproachHold(Actor)"));
    }
}

// 清除外部等待锁
void AEnemyAIController::ClearExternalApproachHold()
{
    bExternalApproachHold = false;
    bExternalHoldUseFaceLocation = false;
    ExternalHoldFaceLocation = FVector::ZeroVector;
    ExternalHoldFaceActor.Reset();
    
    // 不在互动中、也不暂停时恢复BT
    if (!bIsAIPaused && !bIsRunningPendingInteraction)
    {
        if (UBrainComponent* Brain = GetBrainComponent())
        {
            Brain->RestartLogic();
        }
    }
}

// ===== 交谈行为 =====
// 是否为交谈行为
bool AEnemyAIController::IsChatLikeInteraction(const FGameplayTag& ActionTag) const
{
    if(!ActionTag.IsValid())
    {
        return false;
    }

    static const FGameplayTag ChatBehaviorRootTag = FGameplayTag::RequestGameplayTag(FName("Behavior.AI.Interact.Talk"), false);

    if(!ChatBehaviorRootTag.IsValid())
    {
        return false;
    }
    return ActionTag.MatchesTag(ChatBehaviorRootTag);
}

bool AEnemyAIController::IsSleepInteraction(const FGameplayTag& ActionTag) const
{
    return SleepActionTag.IsValid() && ActionTag.IsValid() && ActionTag.MatchesTag(SleepActionTag);
}

bool AEnemyAIController::IsSitInteraction(const FGameplayTag& ActionTag) const
{
    return SitActionTag.IsValid() && ActionTag.IsValid() && ActionTag.MatchesTag(SitActionTag);
}

void AEnemyAIController::ApplySpecialObjectInteractionRuntimeFlags(AEnemyBase* SelfEnemy, const FGameplayTag& ActionTag)
{
    bInteractionDisableAllSenses = false;
    bInteractionSuppressInterestUntilChase = false;

    if (!SelfEnemy || !ActionTag.IsValid())
    {
        return;
    }

    if (IsSleepInteraction(ActionTag))
    {
        bInteractionDisableAllSenses = true;
        Alertness = 0.0f;
        bHasHeardStimulus = false;
        LastHeardLocation = FVector::ZeroVector;
        LastHeardGameTime = -1.0f;
    }
    else if (IsSitInteraction(ActionTag))
    {
        bInteractionSuppressInterestUntilChase = true;
    }

    if (UBlackboardComponent* BB = GetBlackboardComponent())
    {
        if (bInteractionDisableAllSenses || bInteractionSuppressInterestUntilChase)
        {
            BB->SetValueAsBool(BB_HasInterest, false);
            BB->SetValueAsBool(BB_IsInvestigating, false);
            BB->SetValueAsBool(BB_IsChasing, false);
            BB->SetValueAsBool(BB_HasVisualContact, false);
            BB->SetValueAsFloat(BB_Alertness, Alertness);
            BB->ClearValue(BB_HeardLocation);
        }
    }
}

void AEnemyAIController::ClearSpecialObjectInteractionRuntimeFlags()
{
    bInteractionDisableAllSenses = false;
    bInteractionSuppressInterestUntilChase = false;
}

void AEnemyAIController::SnapToObjectInteractionAnchor(AEnemyBase* SelfEnemy, AActor* TargetActor, const FGameplayTag& ActionTag) const
{
    if (!SelfEnemy || !TargetActor || Cast<AEnemyBase>(TargetActor))
    {
        return;
    }

    if (!IsSleepInteraction(ActionTag) && !IsSitInteraction(ActionTag))
    {
        return;
    }

    FVector SnapLocation = TargetActor->GetActorLocation();
    FRotator SnapRotation = SelfEnemy->GetActorRotation();

    TArray<USceneComponent*> SceneComponents;
    TargetActor->GetComponents<USceneComponent>(SceneComponents);
    for (USceneComponent* SceneComp : SceneComponents)
    {
        if (!SceneComp || SceneComp == TargetActor->GetRootComponent())
        {
            continue;
        }

        if (SceneComp->GetFName() == ObjectInteractionAnchorComponentName)
        {
            SnapLocation = SceneComp->GetComponentLocation();
            SnapRotation = SceneComp->GetComponentRotation();
            break;
        }
    }

    // 没有锚点时，使用目标物体朝向，避免坐下/躺下时朝向随机。
    if (SnapRotation.IsNearlyZero())
    {
        SnapRotation = TargetActor->GetActorRotation();
    }

    SelfEnemy->TeleportTo(SnapLocation, FRotator(0.0f, SnapRotation.Yaw, 0.0f), false, true);
}

// 应用互动朝向
void AEnemyAIController::ApplyInteractionFacing(AEnemyBase* SelfEnemy, AActor* TargetActor, float DeltaSeconds) const
{
    if(!SelfEnemy || !TargetActor)
    {
        return;
    }

    const float Dt = FMath::Max(DeltaSeconds, KINDA_SMALL_NUMBER);

    const FVector ToTarget = (TargetActor->GetActorLocation() - SelfEnemy->GetActorLocation()).GetSafeNormal2D();
    if(!ToTarget.IsNearlyZero())
    {
        RotateActorToward(SelfEnemy, TargetActor->GetActorLocation(), Dt);
    }

    if(AEnemyBase* TargetEnemy = Cast<AEnemyBase>(TargetActor))
    {
        const FVector ToSource = (SelfEnemy->GetActorLocation() - TargetEnemy->GetActorLocation()).GetSafeNormal2D();

        if(!ToSource.IsNearlyZero())
        {
            RotateActorToward(TargetEnemy, SelfEnemy->GetActorLocation(), Dt);
        }
    }
    
}

// 处理应用状态互动锁
void AEnemyAIController::ApplyInteractionStateLock(AEnemyBase* SelfEnemy, AActor* TargetActor, const FGameplayTag& ActionTag, bool bIsChatLike)
{
    if(!SelfEnemy || !TargetActor || !ActionTag.IsValid())
    {
        return;
    }

    // 源AI进入互动Tag锁
    SetForcedInteractionStateTag(true, ActionTag);

    // 聊天类互动才同步锁目标
    if (!bIsChatLike || !bChattyLockTargetState)
    {
        return;
    }

    if (AEnemyBase* TargetEnemy = Cast<AEnemyBase>(TargetActor))
    {
        if (AEnemyAIController* TargetCtrl = Cast<AEnemyAIController>(TargetEnemy->GetController()))
        {
            ActiveInteractionTargetController = TargetCtrl;
            TargetCtrl->SetForcedInteractionStateTag(true, ActionTag);
        }
    }
    
}

// 上下文检验（用于校验当前代码是否存在问题）
bool AEnemyAIController::ValidatePendingInteractionContext(const TCHAR* Phase) const
{
    if(!PendingInteractionContext.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("[Interaction][%s] 上下文无效"), Phase);
        return false;
    }

    if(!IsValid(PendingInteractionContext.TargetActor.Get()))
    {
        UE_LOG(LogTemp, Warning, TEXT("[Interaction][%s] 目标不存在"), Phase);
        return false;
    }

    if(!IsValid(PendingInteractionContext.SourceActor.Get()))
    {
        UE_LOG(LogTemp, Warning, TEXT("[Interaction][%s] 源ai不存在"), Phase);
        return false;
    }

    if(!PendingInteractionContext.Spec.ActionTag.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("[Interaction][%s] 行为Tag不存在"), Phase);
        return false;
    }

    return true;
}


// ===== 斗殴运动扭曲功能 =====
// 是否为斗殴行为
bool AEnemyAIController::IsBrawlInteraction(const FGameplayTag& ActionTag) const
{
    if(!ActionTag.IsValid() || !BrawlBehaviorRootTag.IsValid())
    {
        return false;
    }
    return ActionTag.MatchesTag(BrawlBehaviorRootTag);
}

// 应用斗殴运动扭曲
void AEnemyAIController::ApplyBrawlMotionWarping(AEnemyBase* SelfEnemy, AActor* TargetActor, const FGameplayTag& ActionTag) const
{
    if (!bEnableBrawlMotionWarping || !SelfEnemy || !TargetActor || !IsBrawlInteraction(ActionTag))
    {
        return;
    }

    // 获取双方运动扭曲组件
    UMotionWarpingComponent* SelfWarp = SelfEnemy->FindComponentByClass<UMotionWarpingComponent>();
    AEnemyBase* TargetEnemy = Cast<AEnemyBase>(TargetActor);
    UMotionWarpingComponent* TargetWarp = TargetEnemy ? TargetEnemy->FindComponentByClass<UMotionWarpingComponent>() : nullptr;

    // 如果双方没有运动扭曲组件，则不应用斗殴运动扭曲
    if(!SelfWarp || !TargetWarp)
    {
        return;
    }

    // 获取双方位置
    const FVector SelfLoc = SelfEnemy->GetActorLocation();
    const FVector TargetLoc = TargetEnemy->GetActorLocation();

    // 获取双方朝向向量
    FVector Dir = (TargetLoc - SelfLoc).GetSafeNormal2D();
    if(Dir.IsNearlyZero())
    {
        Dir = SelfEnemy->GetActorForwardVector().GetSafeNormal2D();
    }

    // 获取双方中间位置
    const FVector Mid = (SelfLoc + TargetLoc) * 0.5f;

    // 斗殴间距的一半：最小10cm，否则使用配置的 BrawlHalfSpacing
    // 控制两个角色斗殴时的距离
    const float HalfDist = FMath::Max(10.0f, BrawlHalfSpacing);


    const FVector SourceAnchor = Mid - Dir * HalfDist;  // 源角色锚点
    const FVector TargetAnchor = Mid + Dir * HalfDist;  // 目标角色锚点

    const FRotator SourceRot = (TargetAnchor - SourceAnchor).Rotation();  // 源角色旋转
    const FRotator TargetRot = (SourceAnchor - TargetAnchor).Rotation();  // 目标角色旋转

    // 为源角色设置运动扭曲锚点
    if (SelfWarp)
    {
        SelfWarp->AddOrUpdateWarpTargetFromLocationAndRotation(BrawlWarpTargetName, SourceAnchor, SourceRot);
    }
    // 为目标角色设置运动扭曲锚点
    if (TargetWarp)
    {
        TargetWarp->AddOrUpdateWarpTargetFromLocationAndRotation(BrawlWarpTargetName, TargetAnchor, TargetRot);
    }
}


// ===== 头顶文本显示功能 =====
// 互动开始时显示头顶文本
void AEnemyAIController::TryShowInteractionDialogueBubble(
    AEnemyBase* SelfEnemy,
    AActor* TargetActor,
    const FGameplayTag& ActionTag,
    bool bIsChatLike,
    bool bUseDelay
)
{
    if(!bEnableInteractionDialogueBubble || !SelfEnemy || !ActionTag.IsValid())
    {
        return;
    }

    UGameInstance* GI = GetGameInstance();
    UAIBehaviorDialogueSubsystem* DialogueSub = GI ? GI->GetSubsystem<UAIBehaviorDialogueSubsystem>() : nullptr;
    if(!DialogueSub)
    {
        return;
    }

    // 获取源AI文本
    FText SourceLine;
    FGameplayTag SourceMatchedTag;
    const bool bHasSourceLine = DialogueSub->TryGetDialogueLine(GetWorld(), ActionTag, SourceLine, SourceMatchedTag);
    if(!bHasSourceLine || SourceLine.IsEmpty())
    {
        return;
    }

    // 仅在首次展示时清理并使用延迟队列，避免自动刷新时重复取消未执行任务
    if (bUseDelay)
    {
        ClearDialogueBubbleDelayTimers();
    }

    // 延时显示源AI对话（自动刷新时直接更新）
    const float RealSourceDelay = (bUseDelay && bEnableStaggeredChatBubble) ? SourceBubbleDelay : 0.0f;
    ScheduleDialogueBubble(SelfEnemy, SourceLine, RealSourceDelay, SourceBubbleDelayTimerHandle);

    // 非聊天行为不显示
    if(!bIsChatLike)
    {
        return;
    }

    AEnemyBase* TargetEnemy = Cast<AEnemyBase>(TargetActor);
    if(!TargetEnemy)
    {
        return;
    }

    // 获取目标AI文本
    FText TargetLine;
    FGameplayTag TargetMatchedTag;
    bool bHasTargetLine = DialogueSub->TryGetDialogueLine(GetWorld(), ActionTag, TargetLine, TargetMatchedTag);

    // 若文本与源AI抽取的相同重新抽取（最多两次）
    for(int32 Retry = 0;Retry < 2 && bHasTargetLine && !TargetLine.IsEmpty() && TargetLine.EqualTo(SourceLine);Retry++)
    {
        bHasTargetLine = DialogueSub->TryGetDialogueLine(GetWorld(), ActionTag, TargetLine, TargetMatchedTag);
    }

    // 如果抽取不到，则使用源AI文本
    if(!bHasTargetLine || TargetLine.IsEmpty())
    {
        TargetLine = SourceLine;
    }

    // 创建延迟任务，延迟显示目标AI文本
    if(bIsChatLike)
    {
        if(TargetEnemy)
        {
            const float RealTargetDelay = (bUseDelay && bEnableStaggeredChatBubble) ? TargetBubbleDelay : 0.0f;
            ScheduleDialogueBubble(TargetEnemy, TargetLine, RealTargetDelay, TargetBubbleDelayTimerHandle);
        }
    }


}


// 对话延迟显示
void AEnemyAIController::ScheduleDialogueBubble(AEnemyBase* InEnemy, const FText& InLine, float InDelay, FTimerHandle& InHandle)
{
    if(!InEnemy || InLine.IsEmpty())
    {
        return;
    }

    // 清理旧计时器
    GetWorldTimerManager().ClearTimer(InHandle);

    if(InDelay <= KINDA_SMALL_NUMBER)
    {
        InEnemy->ShowDialogueBubble(InLine);
        return;
    }

    TWeakObjectPtr<AEnemyBase> WeakEnemy = InEnemy;
    FTimerDelegate Delegate;
    Delegate.BindWeakLambda(this, [WeakEnemy, InLine]()
        {
            if(WeakEnemy.IsValid())
            {
                WeakEnemy->ShowDialogueBubble(InLine);
            }
        }
    );

    GetWorldTimerManager().SetTimer(InHandle, Delegate, InDelay, false);
}

// 清除延迟显示计时器
void AEnemyAIController::ClearDialogueBubbleDelayTimers()
{
    GetWorldTimerManager().ClearTimer(SourceBubbleDelayTimerHandle);
    GetWorldTimerManager().ClearTimer(TargetBubbleDelayTimerHandle);
}

// 开启对话自动刷新
void AEnemyAIController::StartDialogueRefreshLoop(
    AEnemyBase* SelfEnemy,
    AActor* TargetActor,
    const FGameplayTag& ActionTag,
    bool bIsChatLike)
{
    StopDialogueRefreshLoop();

    if (!bEnableDialogueAutoRefresh || !bEnableInteractionDialogueBubble || !SelfEnemy || !TargetActor || !ActionTag.IsValid())
    {
        return;
    }

    const float Interval = FMath::Max(DialogueRefreshInterval, 0.1f);
    const float FirstDelay = DialogueStartDelay > KINDA_SMALL_NUMBER ? DialogueStartDelay : Interval;

    TWeakObjectPtr<AEnemyBase> WeakSelfEnemy = SelfEnemy;
    TWeakObjectPtr<AActor> WeakTargetActor = TargetActor;

    FTimerDelegate RefreshDelegate;
    RefreshDelegate.BindWeakLambda(this, [this, WeakSelfEnemy, WeakTargetActor, ActionTag, bIsChatLike]()
    {
        if (!bIsRunningPendingInteraction)
        {
            return;
        }

        AEnemyBase* ValidSelfEnemy = WeakSelfEnemy.Get();
        AActor* ValidTargetActor = WeakTargetActor.Get();
        if (!ValidSelfEnemy || !ValidTargetActor)
        {
            return;
        }

        // 自动刷新时直接替换文本，不再使用延迟队列，避免刷新与延迟互相覆盖
        TryShowInteractionDialogueBubble(ValidSelfEnemy, ValidTargetActor, ActionTag, bIsChatLike, false);
    });

    GetWorldTimerManager().SetTimer(
        DialogueRefreshTimerHandle,
        RefreshDelegate,
        Interval,
        true,
        FirstDelay
    );
}

// 停止对话自动刷新
void AEnemyAIController::StopDialogueRefreshLoop()
{
    GetWorldTimerManager().ClearTimer(DialogueRefreshTimerHandle);
}

// 隐藏头顶文本
void AEnemyAIController::HideInteractionDialogueBubble(AEnemyBase* SelfEnemy, AActor* TargetActor) const
{
    if(!bEnableInteractionDialogueBubble)
    {
        return;
    }

    if(SelfEnemy)
    {
        SelfEnemy->HideDialogueBubble();
    }

    if(AEnemyBase* TargetEnemy = Cast<AEnemyBase>(TargetActor))
    {
        TargetEnemy->HideDialogueBubble();
    }
}


// ===== 游戏结束 =====
// 进入游戏结束开火状态
void AEnemyAIController::EnterGameOverFire(AActor* TargetActor)
{
    StopMovement();
    GetWorldTimerManager().ClearTimer(DetectionTimerHandle);
    GetWorldTimerManager().ClearTimer(PendingInteractionTimerHandle);
    GetWorldTimerManager().ClearTimer(InteractionFacingTimerHandle);
    GetWorldTimerManager().ClearTimer(InjectedPathTurnTimerHandle);
    ResetInjectedPathTurnState();
    StopDialogueRefreshLoop();
    ClearDialogueBubbleDelayTimers();

    bUseForcedInteractionStateTag = false;
    ForcedInteractionStateTag = FGameplayTag();
    
    if(UBrainComponent* Brain = GetBrainComponent())
    {
        Brain->StopLogic(TEXT("游戏结束开火状态"));
    }

    if(APawn* ControlledPawn = GetPawn())
    {
        if(UCharacterMovementComponent* MoveComp = ControlledPawn->FindComponentByClass<UCharacterMovementComponent>())
        {
            MoveComp->StopMovementImmediately();
        }

        if(TargetActor)
        {
            const FVector ToTarget = (TargetActor->GetActorLocation() - ControlledPawn->GetActorLocation()).GetSafeNormal2D();
            if(!ToTarget.IsNearlyZero())
            {
                ControlledPawn->SetActorRotation(ToTarget.Rotation());
            }
        }
    }

    if(UBlackboardComponent* BB = GetBlackboardComponent())
    {
        BB->SetValueAsBool(BB_IsFiring, true);
        BB->SetValueAsBool(BB_IsChasing, false);
        BB->SetValueAsBool(BB_IsInvestigating, false);
        BB->SetValueAsBool(BB_HasInterest, false);
    }

    if (!Tag_AI_Fire.IsValid())
    {
        Tag_AI_Fire = FGameplayTag::RequestGameplayTag(FName("State.AI.Combat.Fire"));
    }

    if (AEnemyBase* Enemy = Cast<AEnemyBase>(GetPawn()))
    {
        Enemy->SetAIStateTag(Tag_AI_Fire);
    }
}



// ===== 状态机 =====
// 初始化状态标签
void AEnemyAIController::InitAIStateTags()
{
    Tag_AI_Idle = FGameplayTag::RequestGameplayTag(FName("State.AI.Idle"));
    Tag_AI_Patrol = FGameplayTag::RequestGameplayTag(FName("State.AI.Patrol"));
    Tag_AI_AlertLook = FGameplayTag::RequestGameplayTag(FName("State.AI.Alert.LookAtInterest"));
    Tag_AI_AlertMove = FGameplayTag::RequestGameplayTag(FName("State.AI.Alert.MoveToInterest"));
    Tag_AI_Fire = FGameplayTag::RequestGameplayTag(FName("State.AI.Combat.Fire"));
}

// 更新状态标签
void AEnemyAIController::UpdateAIStateTags()
{
    


    UBlackboardComponent* BB = GetBlackboardComponent();
    AEnemyBase* Enemy = Cast<AEnemyBase>(GetPawn());
    if (!BB || !Enemy) return;

    // 如果启用强制状态 Tag 锁，则直接返回
    if (bUseForcedInteractionStateTag && ForcedInteractionStateTag.IsValid())
    {
        Enemy->SetAIStateTag(ForcedInteractionStateTag);
        return;
    }

    const bool bIsFiring       = BB->GetValueAsBool(BB_IsFiring);
    const bool bHasInterest    = BB->GetValueAsBool(BB_HasInterest);
    const bool bInvestigating  = BB->GetValueAsBool(BB_IsInvestigating);
    const bool bIsChasing      = BB->GetValueAsBool(BB_IsChasing);

    const float Speed2D = GetPawn() ? GetPawn()->GetVelocity().Size2D() : 0.f;
    const bool bIsMoving = Speed2D > 10.f;

    FGameplayTag NewTag = Tag_AI_Idle;

    // 优先级：Fire > LookAtInterest > MoveToInterest > Patrol > Idle
    if (bIsFiring)
    {
        NewTag = Tag_AI_Fire;
    }
    else if (bHasInterest && bInvestigating)
    {
        NewTag = Tag_AI_AlertLook;
    }
    else if (bHasInterest && !bInvestigating && bIsChasing)
    {
        NewTag = Tag_AI_AlertMove;
    }
    else if (bIsMoving)
    {
        NewTag = Tag_AI_Patrol;
    }
    
    Enemy->SetAIStateTag(NewTag);
}
