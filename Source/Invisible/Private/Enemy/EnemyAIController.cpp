// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAIController.h"
#include "Enemy/EnemyBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "BrainComponent.h" 
#include "InvisibleGameStateBase.h"
#include "Perception/AISense_Hearing.h"

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


AEnemyAIController::AEnemyAIController()
{
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


void AEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    AEnemyBase* Enemy = Cast<AEnemyBase>(InPawn);
    if(!Enemy) return;

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
    // PreLookPauseTime    = Cfg.PreLookPauseTime;

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
}

// 停止定时视野检测
void AEnemyAIController::OnUnPossess()
{
    if (AInvisibleGameStateBase* GS = GetWorld()->GetGameState<AInvisibleGameStateBase>())
    {
        GS->OnGlobalHearingRangeChanged.RemoveDynamic(this, &AEnemyAIController::HandleGlobalHearingRangeChanged);
    }

    GetWorldTimerManager().ClearTimer(DetectionTimerHandle);
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


// 定时检测玩家是否在视野范围内
void AEnemyAIController::TickDetection()
{
    if(bIsAIPaused) return;

    UBlackboardComponent* BB = GetBlackboardComponent();
    if (!BB) return;

    const float NowTime = GetWorld()->GetTimeSeconds();
    const float Dt = FMath::Max(DetectionInterval, KINDA_SMALL_NUMBER);

    // ===== 刺激检测 =====
    float Distance = 0.f;
    const bool bInSight = IsPlayerInFanSight(Distance);
    const bool bHeardValid = bHasHeardStimulus && (NowTime - LastHeardGameTime <= HearingMaxAge);
    const bool bHasAnyStimulus = bInSight || bHeardValid;
    ACharacter* Player = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    // ===== 警戒值更新 =====
    if (bInSight)
        Alertness += GetAlertGainRateByDistance(Distance) * Dt;
    else if (bHeardValid)
        Alertness += (HearingAlertGain / FMath::Max(HearingMaxAge, 0.1f)) * Dt;
    else
        Alertness -= AlertDecayRate * Dt;

    Alertness = FMath::Clamp(Alertness, 0.f, MaxAlertness);
    const bool bChasing = (Alertness >= ChaseThreshold);

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
    if (bHasAnyStimulus && !bPrevHasInterest)
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
    const EPathFollowingRequestResult::Type Req = MoveToLocation(Goal, 30.0f, false, true, true, false, nullptr, true);
    
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
