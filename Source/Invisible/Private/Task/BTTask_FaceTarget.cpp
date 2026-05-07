// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTask_FaceTarget.h"

#include "AIController.h"
#include "Enemy/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

UBTTask_FaceTarget::UBTTask_FaceTarget()
{
    NodeName = TEXT("Face Target");
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_FaceTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    APawn* Pawn = AIController ? AIController->GetPawn() : nullptr;
    UBlackboardComponent* BB = AIController ? AIController->GetBlackboardComponent() : nullptr;

    if(!AIController || !Pawn || !BB)
    {
        return EBTNodeResult::Failed;
    }

    // FaceTask 不再自启动Investigating，只消费控制器写入的 true
    const bool bInvestigating = BB->GetValueAsBool(AEnemyAIController::BB_IsInvestigating);
    if (!bInvestigating)
    {
        return EBTNodeResult::Failed;
    }


    const float ClampedFaceDuration = FMath::Max(0.0f, FaceDuration);

    // 获取视觉目标
    FVector TargetLocation = FVector::ZeroVector;
    TargetLocation = BB->GetValueAsVector(InterestLocationKey.SelectedKeyName);
    if (TargetLocation.IsNearlyZero())
    {
        TargetLocation = BB->GetValueAsVector(LastSeenLocationKey.SelectedKeyName);
    }
    // AActor* VisualTarget = Cast<AActor>(BB->GetValueAsObject(VisualTargetActorKey.SelectedKeyName));
    // if(VisualTarget)
    // {
    //     TargetLocation = VisualTarget->GetActorLocation();
    // }
    // else
    // {
    //     // 没有视觉目标，回退到最后目击点
    //     TargetLocation = BB->GetValueAsVector(LastSeenLocationKey.SelectedKeyName);
    // }

    // 玩家位置-自身位置，得到朝向向量，并归一化，保留2d平面向量
    const FVector ToTarget = (TargetLocation - Pawn->GetActorLocation()).GetSafeNormal2D();
    FBTTask_FaceTargetMemory* Memory = reinterpret_cast<FBTTask_FaceTargetMemory*>(NodeMemory);

    // 先进入打探态
    if (AEnemyAIController* EnemyAI = Cast<AEnemyAIController>(AIController))
    {
        EnemyAI->ExtendInterestHoldTime(FMath::Max(0.2f, ClampedFaceDuration));
    }
    // BB->SetValueAsBool(AEnemyAIController::BB_IsInvestigating, true);

    // 停下关闭"随移动转向"，避免与移动系统的旋转冲突
    AIController->StopMovement();
    if(UCharacterMovementComponent* MoveComp = Pawn->FindComponentByClass<UCharacterMovementComponent>())
    {
        // 缓存原有的转向设置，便于未来恢复
        Memory->bCachedOrientRotationToMovement = MoveComp->bOrientRotationToMovement;
        Memory->bHasCachedMoveSetting = true;
        MoveComp->bOrientRotationToMovement = false;
        MoveComp->StopMovementImmediately();
    }

    // 近距离：不要立即 Succeeded，给一个最短的 InProgress 时间
    if (ToTarget.IsNearlyZero())
    {
        Memory->TargetYaw = Pawn->GetActorRotation().Yaw;
        Memory->ElapsedTime = 0.0f;
        return EBTNodeResult::InProgress;
    }

    Memory->TargetYaw = ToTarget.Rotation().Yaw;
    Memory->ElapsedTime = 0.0f;

    // const float CurrentYaw = Pawn->GetActorRotation().Yaw;
    // const float DeltaYaw = FMath::Abs(FMath::FindDeltaAngleDegrees(CurrentYaw, Memory->TargetYaw));
    // if(DeltaYaw <= AcceptYawError)
    // {
    //     return EBTNodeResult::Succeeded;
    // }

    return EBTNodeResult::InProgress;
}

void UBTTask_FaceTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    APawn* Pawn = AIController ? AIController->GetPawn() : nullptr;
    UBlackboardComponent* BB = AIController ? AIController->GetBlackboardComponent() : nullptr;

    if(!Pawn || !BB || !AIController)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    // 追击阈值到达时提前退出看向任务，让 BT 立刻切换到追击分支
    if (BB->GetValueAsBool(AEnemyAIController::BB_IsChasing))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return;
    }

    FBTTask_FaceTargetMemory* Memory = reinterpret_cast<FBTTask_FaceTargetMemory*>(NodeMemory);

    if(bTrackTargetDuringFace)
    {
        FVector TargetLocation = FVector::ZeroVector;
        TargetLocation = BB->GetValueAsVector(InterestLocationKey.SelectedKeyName);
        // if(AActor* VisualTarget = Cast<AActor>(BB->GetValueAsObject(VisualTargetActorKey.SelectedKeyName)))
        // {
        //     TargetLocation = VisualTarget->GetActorLocation();
        // }
        // else
        // {
        //     TargetLocation = BB->GetValueAsVector(LastSeenLocationKey.SelectedKeyName);
        // }
        if (TargetLocation.IsNearlyZero())
        {
            TargetLocation = BB->GetValueAsVector(LastSeenLocationKey.SelectedKeyName);
        }

        const FVector ToTarget = (TargetLocation - Pawn->GetActorLocation()).GetSafeNormal2D();
        if(!ToTarget.IsNearlyZero())
        {
            Memory->TargetYaw = ToTarget.Rotation().Yaw;
        }
    }

    const float CurrentYaw = Pawn->GetActorRotation().Yaw;
    const float DeltaYaw = FMath::FindDeltaAngleDegrees(CurrentYaw, Memory->TargetYaw);
    const float MaxStep = TurnSpeed * DeltaSeconds;
    const float Step = FMath::Clamp(DeltaYaw, -MaxStep, MaxStep);
    const float NewYaw = FRotator::NormalizeAxis(CurrentYaw + Step);

    Pawn->SetActorRotation(FRotator(0.0f, NewYaw, 0.0f));

    // const float Remain = FMath::Abs(FMath::FindDeltaAngleDegrees(NewYaw, Memory->TargetYaw));
    // if(Remain <= AcceptYawError)
    // {
    //     FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    // }

    Memory->ElapsedTime += DeltaSeconds;
    const float ClampedFaceDuration = FMath::Max(0.0f, FaceDuration);
    if(Memory->ElapsedTime >= ClampedFaceDuration)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return;
    }
}

void UBTTask_FaceTarget::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* Pawn = AIController ? AIController->GetPawn() : nullptr;
    UBlackboardComponent* BB = AIController ? AIController->GetBlackboardComponent() : nullptr;
	FBTTask_FaceTargetMemory* Memory = reinterpret_cast<FBTTask_FaceTargetMemory*>(NodeMemory);

    if (BB)
    {
        BB->SetValueAsBool(AEnemyAIController::BB_IsInvestigating, false);
    }

    // 还原原有移动设置
	if (Pawn && Memory->bHasCachedMoveSetting)
	{
		if (UCharacterMovementComponent* MoveComp = Pawn->FindComponentByClass<UCharacterMovementComponent>())
		{
			MoveComp->bOrientRotationToMovement = Memory->bCachedOrientRotationToMovement;
		}
	}
}

uint16 UBTTask_FaceTarget::GetInstanceMemorySize() const
{
    return sizeof(FBTTask_FaceTargetMemory);
}
