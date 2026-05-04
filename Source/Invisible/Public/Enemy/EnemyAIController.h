// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "InvisibleGameStateBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Navigation/PathFollowingComponent.h"
#include "GameplayTagContainer.h"
#include "Enemy/Interaction/AIInteractionTypes.h"
#include "EnemyAIController.generated.h"

class APlayerCharacter;

// 广播事件结束信息
DECLARE_MULTICAST_DELEGATE_FourParams(
    FOnInteractionResolvedNative,
    AActor* /*SourceActor*/,
    AActor* /*TargetActor*/,
    FGameplayTag /*ActionTag*/,
    EInteractionEndReason /*EndReason*/);

/**
 * 敌人AI控制器，负责敌人的AI行为和感知
 */
UCLASS()
class INVISIBLE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
    virtual void Tick(float DeltaSeconds) override;

    // 广播事件结束信息
    FOnInteractionResolvedNative OnInteractionResolvedNative;

public:
    AEnemyAIController();
	virtual void OnPossess(APawn* InPawn) override;
    virtual void OnUnPossess() override;

    // 暂停角色，供编辑模式切换时调用
    UFUNCTION(BlueprintCallable, Category = "AI")
    void SetAIPaused(bool bPaused);

    // 启用视觉机制，可在结束暂停，供恢复时调用
    UFUNCTION(BlueprintCallable, Category = "AI")
    void StartDetectionTimer();


    // =====警戒值获取=====

    // 获取实际警戒值
    UFUNCTION(BlueprintPure, Category="AI|Perception|Alert")
    float GetAlertness() const { return Alertness; }

    // 获取警戒值百分比
    UFUNCTION(BlueprintPure, Category="AI|Perception|Alert")
    float GetAlertnessNormalized() const
    {
        return MaxAlertness > 0.f ? Alertness / MaxAlertness : 0.f;
    }


    // 设置编辑模式绘制后的临时路径（退出编辑模式后执行）
    UFUNCTION(BlueprintCallable, Category = "AI|InjectedPath")
    void SetInjectedPath(const TArray<FVector>& InPathPoints);

    // ===== ai交互功能 =====

    // 设置待执行互动（在编辑模式结束后，ai行走到目标点执行）
    UFUNCTION(BlueprintCallable, Category = "AI|Interaction")
    void SetPendingInteractionContext(const FTraitInteractionContext& InContext);

    // 清除待执行互动
    UFUNCTION(BlueprintCallable, Category="AI|Interaction")
    void ClearPendingInteraction();

    // 待执行互动开始事件（暴露给蓝图，用于在互动开始时执行动画或者对话等）
    UFUNCTION(BlueprintImplementableEvent, Category="AI|Interaction")
    void BP_OnPendingInteractionStarted(AActor* TargetActor, FGameplayTag BehaviorTag, float Duration);
    
    // 待执行互动完成事件（暴露给蓝图，用于在互动完成时执行动画或者对话等）
    UFUNCTION(BlueprintImplementableEvent, Category="AI|Interaction")
    void BP_OnPendingInteractionFinished(AActor* TargetActor, FGameplayTag BehaviorTag);

    // 待执行互动中断事件（暴露给蓝图，用于在互动中断时执行动画或者对话等）
    UFUNCTION(BlueprintImplementableEvent, Category="AI|Interaction")
    void BP_OnPendingInteractionInterrupted(AActor* TargetActor, FGameplayTag BehaviorTag);

    // 达到打探阈值时是否打断当前互动行为
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Interaction")
    bool bInterruptInteractionOnChase = true;

    // 中断当前待执行互动
    void InterruptPendingInteractionForAlert();

public:

    // ===== 交谈行为 =====
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Interaction")
    bool bChattyLockTargetState = true;

    // ===== 交互相关参数 =====
    // ===== 外部等待锁（用于“目标AI原地等待”）=====

    // 目标朝向A走到的预估位置
    void SetExternalApproachHoldByLocation(const FVector& InFaceLocation);

    // 目标朝向最终修正到A走到的位置
    void SetExternalApproachHoldByActor(AActor* InFaceActor);

    // 清除外部等待锁
    void ClearExternalApproachHold();

    // 是否存在外部等待锁
    bool HasExternalApproachHold() const { return bExternalApproachHold; }


private:
    // ===== 交互相关参数 =====
    // 互动时转向速度（从 EnemyBase 获取）
    float InteractionTurnSpeed = 360.0f;

    // 互动时转向计时器
    FTimerHandle InteractionFacingTimerHandle;
    
    // 互动时转向计时器回调
    void TickInteractionFacing();

    // ai转向函数
    void RotateActorToward(AActor* ActorToRotate, const FVector& TargetLocation, float DeltaSeconds) const;

    // ===== 外部等待锁（用于“目标AI原地等待”）=====
    bool bExternalApproachHold = false;

    // 朝向模式：位置优先，其次Actor
    bool bExternalHoldUseFaceLocation = false;
    FVector ExternalHoldFaceLocation = FVector::ZeroVector;
    // 朝向目标Actor
    TWeakObjectPtr<AActor> ExternalHoldFaceActor;
    

    // ===== 交谈行为 =====
    // 当前交谈目标的AI控制器
    TWeakObjectPtr<AEnemyAIController> ActiveInteractionTargetController;

    // 是否为交谈行为
    bool IsChatLikeInteraction(const FGameplayTag& ActionTag) const;

    // 应用互动朝向
    void ApplyInteractionFacing(AEnemyBase* SelfEnemy, AActor* TargetActor, float DeltaSeconds) const;

    // 处理应用状态互动锁
    void ApplyInteractionStateLock(AEnemyBase* SelfEnemy, AActor* TargetActor, const FGameplayTag& ActionTag, bool bIsChatLike);


    // 上下文检验（用于校验当前代码是否存在问题）
    bool ValidatePendingInteractionContext(const TCHAR* Phase) const;

    // ===== 斗殴运动扭曲运行时参数（从EnemyBase同步）=====
    // 是否启用斗殴运动扭曲
    bool bEnableBrawlMotionWarping = true;
    // 斗殴行为根标签
    FGameplayTag BrawlBehaviorRootTag;
    // 斗殴运动扭曲目标名称 
    FName BrawlWarpTargetName = TEXT("BrawlTarget");
    // 斗殴运动扭曲目标半间距
    float BrawlHalfSpacing = 80.0f;

    // 是否为斗殴行为
    bool IsBrawlInteraction(const FGameplayTag& ActionTag) const;
    // 应用斗殴运动扭曲
    void ApplyBrawlMotionWarping(AEnemyBase* SelfEnemy, AActor* TargetActor, const FGameplayTag& ActionTag) const;

private:
    // =====视觉警戒值检测相关=====

    // 最大警戒值
    float MaxAlertness = 100.0f;

    // 实际警戒值
    float Alertness = 0.0f;

    // 三段视觉警戒距离

    // 近距警戒
    float NearRange = 300.f;

    // 中距警戒
    float MidRange = 700.f;

    // 远距警戒
    float FarRange = 1200.f;

    // 三段警戒值增长速率

    // 近距警戒值增长速率
    float NearGainRate = 45.0f;

    // 中距警戒值增长速率
    float MidGainRate = 25.0f;

    // 远距警戒值增长速率
    float FarGainRate = 10.0f;

    // 视野外警戒值衰减速率
    float AlertDecayRate = 20.0f;

    // 玩家站立时视觉警戒值增长倍率
    float StandGainMultiplier = 1.0f;

    // 玩家行走时视觉警戒值增长倍率
    float WalkGainMultiplier = 1.0f;

    // 玩家奔跑时视觉警戒值增长倍率
    float RunGainMultiplier = 1.5f;

    // 玩家蹲下时视觉警戒值增长倍率
    float CrouchIdleGainMultiplier = 0.3f;

    // 玩家蹲走时视觉警戒值增长倍率
    float CrouchWalkGainMultiplier = 0.6f;


    // 状态阈值

    // 怀疑阈值
    float SuspiciousThreshold = 50.f;

    // 打探阈值
    float ChaseThreshold = 80.f;

    // 目标丢失阈值
    float LoseTargetThreshold = 15.f;

    // =====编辑模式插入路径=====

    // 插入路径点
    UPROPERTY()
    TArray<FVector> InjectedPathPoints;

    // 插入路径索引
    int32 InjectedPathIndex = INDEX_NONE;

    // 插入路径完成回调
    FDelegateHandle InjectedPathFinishedHandle;

    // 检查路径是否有效
    bool HasValidInjectedPath() const;

    // 开始插入路径
    void StartInjectedPath();

    // 移动到插入路径点
    void MoveToInjectedPoint(int32 PointIndex);

    // 完成插入路径并恢复巡逻
    void FinishInjectedPathAndResumePatrol();

    // 插入路径完成回调
    void HandleInjectedPathMoveFinished(FAIRequestID RequestID, const FPathFollowingResult& Result);

    // =====编辑模式互动执行（ai行为执行）=====

    // 待执行互动目标
    TWeakObjectPtr<AActor> PendingInteractionTarget;

    // 待执行互动行为标签
    FGameplayTag PendingInteractionBehaviorTag;

    // 待执行互动时长
    float PendingInteractionDuration = 0.0f;

    // 待执行互动执行距离
    float PendingInteractionExecutionRadius = 0.0f;

    // 是否存在待执行互动
    bool bHasPendingInteraction = false;

    // 是否正在执行待执行互动
    bool bIsRunningPendingInteraction = false;

    // 待执行互动计时器
    FTimerHandle PendingInteractionTimerHandle;

    // 待执行互动上下文
    FTraitInteractionContext PendingInteractionContext;

    // 待执行互动完成回调
    FDelegateHandle PendingInteractionApproachFinishedHandle;

    // 检查待执行互动是否有效
    bool HasValidPendingInteraction() const;

    // 开始执行待执行互动
    void StartPendingInteraction();

    // 完成执行待执行互动
    void FinishPendingInteraction();

    // 开始接近目标
    void StartPendingInteractionApproach();

    // 接近目标完成回调
    void HandlePendingInteractionApproachFinished(FAIRequestID RequestID, const FPathFollowingResult& Result);

    // 开始执行
    void BeginPendingInteractionLoop();

    // 强制状态 Tag （用于在互动期间防止被常规状态机覆盖）
    void SetForcedInteractionStateTag(bool bEnable, FGameplayTag InTag);

    // 是否启用强制状态 Tag
    bool bUseForcedInteractionStateTag = false;

    // 强制状态 Tag
    FGameplayTag ForcedInteractionStateTag;

private:
	class UBehaviorTreeComponent* BehaviorTreeComp;	// 行为树组件
	class UBlackboardComponent* BlackboardComp;	// 黑板组件

    // =====视觉检测=====

	// 定时检测玩家（考虑到性能，暂时按时间检测）
    FTimerHandle DetectionTimerHandle;
    void TickDetection();

    // 扇形视野检测
    bool IsPlayerInFanSight(float& OutDistance) const;

    // 按距离返回增速
    float GetAlertGainRateByDistance(float Distance) const;

    // 提交最后看到或者听到的位置
    void CommitInterestLocation(const FVector& Location);

    // 获取玩家状态并得出最终警戒值增长倍率
    float GetPlayerStateAlertMultiplier(const APlayerCharacter* Player) const;

    // 视野参数（从 EnemyBase 读取）
    float SightRadius    = 1200.f;
	
    float HalfViewAngle  = 60.f;   // 半视角，总视角 = 2 * HalfViewAngle

    bool bIsAIPaused = false;    // 是否暂停AI

    // 视觉检测频率（秒）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Perception", meta = (AllowPrivateAccess = "true", ClampMin = "0.02", ClampMax = "1.0", UIMin = "0.02", UIMax = "0.5"))
    float DetectionInterval = 0.1f;

    // 检测上一帧是否看到玩家
    bool bWasInSightLastTick = false;

    // 看向目标点的时间(从EnemyBase中获取)
    float InvestigateLookDuration = 2.0f;

    // 每次听到声音增长的警戒值（从EnemyBase中获取）
    float HearingAlertGain = 10.0f;

    // 视觉首次出现锁，用于看到玩家后，失去视野前
    bool bVisualFirstLock = false;

    // 视觉首次出现点
    FVector FirstSeenLocation = FVector::ZeroVector;

    // 兴趣状态最短保持到该时间（避免 FaceDuration 未结束就被清理）
    float InterestHoldUntilTime = -1.0f;

public:
    // ===== 听觉检测 =====

    // 听觉半径
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI|Perception|Hearing",
        meta=(ClampMin="0.0", UIMin="0.0"))
    float HearingRange = 1500.f;

    // 从游戏状态获取听觉范围
    UFUNCTION(BlueprintCallable, Category="AI|Perception|Hearing")
    void ApplyHearingRangeFromGameState();

    // 处理全局听觉范围变化的回调
    UFUNCTION()
    void HandleGlobalHearingRangeChanged(float NewRange);
    
    // 丢失刺激后的保留时间（秒）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Perception|Hearing",
        meta=(ClampMin="0.0", UIMin="0.0", UIMax="10.0"))
    float HearingMaxAge = 2.0f;

    // 是否需要视线才“听到”
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Perception|Hearing")
    bool bUseLoSHearing = false;

    // 是否启用听觉
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Perception|Hearing")
    bool bEnableHearing = true;
    
    // 运行时重建听觉配置（蓝图可调用）
    /*UFUNCTION(BlueprintCallable, Category="AI|Perception|Hearing")
    void ApplyHearingConfig();*/

private:
    // 感知组件
    UPROPERTY(VisibleAnywhere)
    UAIPerceptionComponent* PerceptionComp;

    // 听觉检测配置
    UPROPERTY(VisibleAnywhere)
    UAISenseConfig_Hearing* HearingConfig;

    // 当前可用听觉刺激
    bool bHasHeardStimulus = false;
    FVector LastHeardLocation = FVector::ZeroVector;
    float LastHeardGameTime = -1.0f;

public:

    // 听到声音的回调（直接接收 FAIStimulus，比 OnPerceptionUpdated+GetActorsPerception 更可靠）
    UFUNCTION()
    void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

    UFUNCTION(BlueprintPure, Category = "AI|Perception|Hearing")
    float GetHearingRange() const { return HearingRange; }

    // MoveTO 后，清除运行时状态
    UFUNCTION(BlueprintCallable, Category="AI|Perception|Investigate")
    void ClearInvestigateRuntimeState(bool bClearHeardMemory = true);

    // 延长兴趣状态最短保持时间，供 BT Task 在启动时注入自身持续时长
    // 保证 TickDetection 的自动清理不会在任务结束前提前触发
    UFUNCTION(BlueprintCallable, Category="AI|Perception|Investigate")
    void ExtendInterestHoldTime(float Duration);


// ===== 头顶文本显示功能 =====
public:
    // 是否启用行为头顶显示
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Interaction")
    bool bEnableInteractionDialogueBubble = true;

    // 是否启用交谈双方错峰显示
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Interaction|Dialogue")
    bool bEnableStaggeredChatBubble = true;

    // 源AI对话框延迟（秒）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Interaction|Dialogue", meta=(ClampMin="0.0"))
    float SourceBubbleDelay = 0.0f;

    // 目标AI对话框延迟（秒）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Interaction|Dialogue", meta=(ClampMin="0.0"))
    float TargetBubbleDelay = 0.35f;

private:
    // 互动开始时显示头顶文本
    void TryShowInteractionDialogueBubble(
        AEnemyBase* SelfEnemy,
        AActor* TargetActor,
        const FGameplayTag& ActionTag,
        bool bIsChatLike
    );

    // 隐藏头顶文本（在互动结束或中断时隐藏）
    void HideInteractionDialogueBubble(
        AEnemyBase* SelfEnemy,
        AActor* TargetActor
    ) const;

    // 源/目标延迟显示计时器
    FTimerHandle SourceBubbleDelayTimerHandle;
    FTimerHandle TargetBubbleDelayTimerHandle;

    // 对话延迟显示
    void ScheduleDialogueBubble(AEnemyBase* InEnemy, const FText& InLine, float InDelay, FTimerHandle& InHandle);

    // 清除延迟显示计时器
    void ClearDialogueBubbleDelayTimers();


// ===== 游戏结束 =====
public:
    // 进入游戏结束开火状态
    UFUNCTION(BlueprintCallable, Category="AI|GameOver")
    void EnterGameOverFire(AActor* TargetActor);


// ===== 状态机 =====
private:
    // AI状态标签缓存
    FGameplayTag Tag_AI_Idle;
    FGameplayTag Tag_AI_Patrol;
    FGameplayTag Tag_AI_AlertLook;
    FGameplayTag Tag_AI_AlertMove;
    FGameplayTag Tag_AI_Fire;   // 预留，用于游戏结束（失败）时播放

    // 初始化状态标签
    void InitAIStateTags();

    // 更新状态标签
    void UpdateAIStateTags();
    
public:



    // Blackboard 键名
    static const FName BB_TargetActor;
    static const FName BB_WaypointBehavior;
    static const FName BB_WaypointWaitTime;
    static const FName BB_LookAngle;
    static const FName BB_LookSpeed;
    static const FName BB_HeardLocation;
    static const FName BB_IsInvestigating;
    static const FName BB_Alertness;
    static const FName BB_HasVisualContact;
    static const FName BB_IsSuspicious;
    static const FName BB_IsChasing;
    static const FName BB_LastSeenLocation;
    static const FName BB_VisualTargetActor;
    static const FName BB_UseLookCenterYaw;
    static const FName BB_LookCenterYaw;
    static const FName BB_PreLookPauseTime;
    static const FName BB_InterestLocation;
    static const FName BB_HasInterest;
    static const FName BB_IsFiring;
};
