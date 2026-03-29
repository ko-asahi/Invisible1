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
    const float ClampedFaceDuration = FMath::Max(0.0f, FaceDuration);

    // 获取视觉目标
    FVector TargetLocation = FVector::ZeroVector;
    TargetLocation = BB->GetValueAsVector(InterestLocationKey.SelectedKeyName);
    if (TargetLocation.IsNearlyZero())
    {
        TargetLocation = BB->GetValueAsVector(LastSeenLocationKey.SelectedKeyName);
    }

    // 玩家位置-自身位置，得到朝向向量，并归一化，保留2d平面向量
    const FVector ToTarget = (TargetLocation - Pawn->GetActorLocation()).GetSafeNormal2D();
    if(ToTarget.IsNearlyZero())
    {
        return EBTNodeResult::Succeeded;
    }

    FBTTask_FaceTargetMemory* Memory = reinterpret_cast<FBTTask_FaceTargetMemory*>(NodeMemory);
    if(!ToTarget.IsNearlyZero())
    {
        Memory->TargetYaw = ToTarget.Rotation().Yaw;
        Memory->ElapsedTime = 0.0f;
    }

    // 将 FaceDuration 注入控制器，确保 TickDetection 的自动清理不会在看向结束前触发
    if (AEnemyAIController* EnemyAI = Cast<AEnemyAIController>(AIController))
    {
        EnemyAI->ExtendInterestHoldTime(ClampedFaceDuration);
    }

    // 进入看向阶段，防止检测逻辑提前清除兴趣状态
    BB->SetValueAsBool(AEnemyAIController::BB_IsInvestigating, true);

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

    FBTTask_FaceTargetMemory* Memory = reinterpret_cast<FBTTask_FaceTargetMemory*>(NodeMemory);

    if(bTrackTargetDuringFace)
    {
        FVector TargetLocation = FVector::ZeroVector;
        TargetLocation = BB->GetValueAsVector(InterestLocationKey.SelectedKeyName);
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
