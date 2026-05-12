// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTask_Patrol.h"
#include "Enemy/EnemyBase.h"
#include "Enemy/EnemyAIController.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

namespace
{
	void WritePatrolBehaviorBlackboard(AEnemyBase* Enemy, UBlackboardComponent* BB, const FPatrolWaypointData& Data, const FVector& AnchorWorldLocation)
	{
		if (!Enemy || !BB)
		{
			return;
		}

		BB->SetValueAsEnum(TEXT("WaypointBehavior"), static_cast<uint8>(Data.Behavior));
		BB->SetValueAsFloat(TEXT("WaypointWaitTime"), Data.WaitTime);
		BB->SetValueAsFloat(TEXT("LookAngle"), Data.LookAngle);
		BB->SetValueAsFloat(TEXT("LookSpeed"), Data.LookSpeed);
		BB->SetValueAsFloat(TEXT("PreLookPauseTime"), Data.PreLookPauseTime);

		float CenterYaw = Enemy->GetActorRotation().Yaw;
		if (Data.bUseCustomLookCenter)
		{
			float AnchorYaw = 0.0f;
			if (Enemy->GetCurrentPatrolBehaviorAnchorYaw(AnchorWorldLocation, AnchorYaw))
			{
				CenterYaw = AnchorYaw;
			}
			CenterYaw = FRotator::NormalizeAxis(CenterYaw + Data.LookCenterYawOffset);
		}
		BB->SetValueAsBool(TEXT("UseLookCenterYaw"), Data.bUseCustomLookCenter);
		BB->SetValueAsFloat(TEXT("LookCenterYaw"), CenterYaw);
	}
}

UBTTask_Patrol::UBTTask_Patrol()
{
	NodeName = TEXT("Patrol Spline Follow");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	AEnemyBase* Enemy = Cast<AEnemyBase>(AIController->GetPawn());
	if (!Enemy)
	{
		return EBTNodeResult::Failed;
	}

	UCharacterMovementComponent* MoveComp = Enemy->GetCharacterMovement();
	if (!MoveComp)
	{
		return EBTNodeResult::Failed;
	}

	FBTTask_PatrolMemory* Memory = reinterpret_cast<FBTTask_PatrolMemory*>(NodeMemory);
	Memory->CachedMaxWalkSpeed = MoveComp->MaxWalkSpeed;
	Memory->bReturningToStart = false;
	MoveComp->MaxWalkSpeed = FMath::Max(1.0f, Enemy->PatrolSpeed * PatrolSpeedScale);

	AIController->StopMovement();

	MoveComp->bOrientRotationToMovement = true;
	if (MoveComp->MovementMode == MOVE_None)
	{
		MoveComp->SetMovementMode(MOVE_Walking);
	}

	float RouteLength = 0.0f;
	if (!Enemy->GetPatrolRouteLength(RouteLength))
	{
		return EBTNodeResult::Failed;
	}

	Memory->RouteLength = RouteLength;

	float ProjectedDist = 0.0f;
	if (!Enemy->ProjectWorldLocationToPatrolDistance(Enemy->GetActorLocation(), ProjectedDist))
	{
		Memory->DistanceAlongRoute = 0.f;
	}
	else
	{
		Memory->DistanceAlongRoute = FMath::Clamp(ProjectedDist, 0.f, RouteLength);
	}

	Enemy->UpdatePatrolBehaviorAnchorCooldown(Enemy->GetActorLocation());

	return EBTNodeResult::InProgress;
}

void UBTTask_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (BB && BB->GetValueAsBool(AEnemyAIController::BB_HasInterest))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	AEnemyBase* Enemy = AIController ? Cast<AEnemyBase>(AIController->GetPawn()) : nullptr;
	if (!AIController || !Enemy)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	UCharacterMovementComponent* MoveComp = Enemy->GetCharacterMovement();
	if (!MoveComp)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	FBTTask_PatrolMemory* Memory = reinterpret_cast<FBTTask_PatrolMemory*>(NodeMemory);

	const float RouteLength = Memory->RouteLength;
	if (RouteLength <= KINDA_SMALL_NUMBER)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	FVector ActorLoc = Enemy->GetActorLocation();
	Enemy->UpdatePatrolBehaviorAnchorCooldown(ActorLoc);

	if (Memory->bReturningToStart)
	{
		FVector StartLoc;
		FRotator StartRot;
		if (!Enemy->GetPatrolRouteTransformAtDistance(0.0f, StartLoc, StartRot))
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return;
		}

		const FVector ReturnDelta(StartLoc.X - ActorLoc.X, StartLoc.Y - ActorLoc.Y, 0.0f);
		const float ReturnAcceptSq = FMath::Square(ReturnToStartAcceptanceRadius);
		if (ReturnDelta.SizeSquared() > ReturnAcceptSq)
		{
			Enemy->AddMovementInput(ReturnDelta.GetSafeNormal(), 1.0f, true);
			return;
		}

		Memory->bReturningToStart = false;
		Memory->DistanceAlongRoute = 0.0f;
		ActorLoc = StartLoc;
	}

	const float PatrolSpeed = FMath::Max(1.0f, Enemy->PatrolSpeed * PatrolSpeedScale);
	Memory->DistanceAlongRoute += PatrolSpeed * DeltaSeconds;
	if (Memory->DistanceAlongRoute >= RouteLength)
	{
		Memory->DistanceAlongRoute = RouteLength;
		Memory->bReturningToStart = true;
		return;
	}

	FVector SplineLoc;
	FRotator SplineRot;
	if (!Enemy->GetPatrolRouteTransformAtDistance(Memory->DistanceAlongRoute, SplineLoc, SplineRot))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	const FVector FlatDelta(SplineLoc.X - ActorLoc.X, SplineLoc.Y - ActorLoc.Y, 0.f);
	if (FlatDelta.SizeSquared() > FMath::Square(5.f))
	{
		Enemy->AddMovementInput(FlatDelta.GetSafeNormal(), 1.f, true);
	}

	int32 NearestIdx = INDEX_NONE;
	float NearestDistSq = 0.f;
	Enemy->TryGetNearestPatrolSplinePointIndex(ActorLoc, NearestIdx, NearestDistSq);

	const FPatrolWaypointData Data = Enemy->GetCurrentPatrolBehaviorData(ActorLoc);
	if (Data.Behavior != EWaypointBehavior::None && NearestIdx != INDEX_NONE && NearestIdx != Enemy->PatrolBehaviorCooldownSplinePointIndex && BB)
	{
		Enemy->PatrolBehaviorCooldownSplinePointIndex = NearestIdx;
		WritePatrolBehaviorBlackboard(Enemy, BB, Data, ActorLoc);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
}

void UBTTask_Patrol::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	FBTTask_PatrolMemory* Memory = reinterpret_cast<FBTTask_PatrolMemory*>(NodeMemory);
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

	if (AEnemyBase* Enemy = AIController ? Cast<AEnemyBase>(AIController->GetPawn()) : nullptr)
	{
		if (UCharacterMovementComponent* MoveComp = Enemy->GetCharacterMovement())
		{
			if (Memory->CachedMaxWalkSpeed >= 0.f)
			{
				MoveComp->MaxWalkSpeed = Memory->CachedMaxWalkSpeed;
				Memory->CachedMaxWalkSpeed = -1.f;
			}
		}
	}

	if (AIController)
	{
		AIController->StopMovement();
		if (TaskResult != EBTNodeResult::Succeeded)
		{
			if (APawn* Pawn = AIController->GetPawn())
			{
				if (UCharacterMovementComponent* MoveComp = Pawn->FindComponentByClass<UCharacterMovementComponent>())
				{
					MoveComp->StopMovementImmediately();
				}
			}
		}
	}
}

uint16 UBTTask_Patrol::GetInstanceMemorySize() const
{
	return sizeof(FBTTask_PatrolMemory);
}
