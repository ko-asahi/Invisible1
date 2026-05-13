// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTask_TurnToWaypoint.h"

#include "AIController.h"
#include "Enemy/EnemyBase.h"
#include "Enemy/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


UBTTask_TurnToWaypoint::UBTTask_TurnToWaypoint()
{
	NodeName = TEXT("Turn To Next Waypoint");
	bNotifyTick = true;
}


EBTNodeResult::Type UBTTask_TurnToWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
    // UE_LOG(LogTemp, Warning, TEXT("[TurnToWaypoint] ExecuteTask entered. AIController=%s"), *GetNameSafe(AIController));
	AEnemyBase* Enemy = AIController ? Cast<AEnemyBase>(AIController->GetPawn()) : nullptr;
    const int32 RoutePointCount = Enemy ? Enemy->GetPatrolRoutePointCount() : 0;
	if (!AIController || !Enemy || RoutePointCount == 0)
	{
        // UE_LOG(LogTemp, Warning, TEXT("[TurnToWaypoint] Failed precheck. Enemy=%s RoutePointCount=%d"), *GetNameSafe(Enemy), RoutePointCount);
		return EBTNodeResult::Failed;
	}

    FVector TargetLocation = FVector::ZeroVector;
    if (!Enemy->GetCurrentPatrolLocation(TargetLocation))
    {
        // UE_LOG(LogTemp, Warning, TEXT("[TurnToWaypoint] Cannot get patrol location. Enemy=%s"), *GetNameSafe(Enemy));
        return EBTNodeResult::Failed;
    }

	FBTTask_TurnToWaypointMemory* Memory = reinterpret_cast<FBTTask_TurnToWaypointMemory*>(NodeMemory);

    // 可配置：关闭原地预转身后，直接进入 MoveTo 阶段，边走边转
    if (!Enemy->bTurnInPlaceBeforePatrolMove)
    {
        return EBTNodeResult::Succeeded;
    }


	// 预转身阶段：停下并关闭“随移动转向”
	if (UCharacterMovementComponent* MoveComp = Enemy->GetCharacterMovement())
	{
		Memory->bCachedOrientRotationToMovement = MoveComp->bOrientRotationToMovement;
		Memory->bHasCachedMoveSetting = true;
		MoveComp->bOrientRotationToMovement = false;
	}
	AIController->StopMovement();
	Enemy->GetCharacterMovement()->StopMovementImmediately();

	const FVector ToTarget = (TargetLocation - Enemy->GetActorLocation()).GetSafeNormal2D();
	if (ToTarget.IsNearlyZero())
	{
		return EBTNodeResult::Succeeded;
	}

	Memory->TargetYaw = ToTarget.Rotation().Yaw;

	const float CurrentYaw = Enemy->GetActorRotation().Yaw;
	const float DeltaYaw = FMath::Abs(FMath::FindDeltaAngleDegrees(CurrentYaw, Memory->TargetYaw));
	if (DeltaYaw < MinTurnAngle)
	{
		// 角度很小，不浪费时间停顿
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::InProgress;
}
void UBTTask_TurnToWaypoint::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	AEnemyBase* Enemy = AIController ? Cast<AEnemyBase>(AIController->GetPawn()) : nullptr;
	if (!Enemy)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	// 检测到兴趣点时立刻中止，确保预转身阶段也可被打断
	if (UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent())
	{
		if (BB->GetValueAsBool(AEnemyAIController::BB_HasInterest))
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return;
		}
	}

	FBTTask_TurnToWaypointMemory* Memory = reinterpret_cast<FBTTask_TurnToWaypointMemory*>(NodeMemory);

	const float CurrentYaw = Enemy->GetActorRotation().Yaw;
    const float DeltaYaw = FMath::FindDeltaAngleDegrees(CurrentYaw, Memory->TargetYaw); // [-180, 180]
    const float MaxStep = TurnSpeed * DeltaSeconds;
    const float Step = FMath::Clamp(DeltaYaw, -MaxStep, MaxStep);
    const float NewYaw = FRotator::NormalizeAxis(CurrentYaw + Step);
    Enemy->SetActorRotation(FRotator(0.f, NewYaw, 0.f));

	const float Remain = FMath::Abs(FMath::FindDeltaAngleDegrees(NewYaw, Memory->TargetYaw));
	if (Remain <= AcceptYawError)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
void UBTTask_TurnToWaypoint::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	AAIController* AIController = OwnerComp.GetAIOwner();
	AEnemyBase* Enemy = AIController ? Cast<AEnemyBase>(AIController->GetPawn()) : nullptr;
	FBTTask_TurnToWaypointMemory* Memory = reinterpret_cast<FBTTask_TurnToWaypointMemory*>(NodeMemory);

	// 结束预转身后恢复，让后续 MoveTo 阶段可边走边转（含避障）
	if (Enemy && Memory->bHasCachedMoveSetting)
	{
		if (UCharacterMovementComponent* MoveComp = Enemy->GetCharacterMovement())
		{
			MoveComp->bOrientRotationToMovement = Memory->bCachedOrientRotationToMovement;
		}
	}
}

uint16 UBTTask_TurnToWaypoint::GetInstanceMemorySize() const
{
	return sizeof(FBTTask_TurnToWaypointMemory);
}