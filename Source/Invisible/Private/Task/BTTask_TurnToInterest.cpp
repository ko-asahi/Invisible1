// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTask_TurnToInterest.h"
#include "AIController.h"
#include "Enemy/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Pawn.h"


UBTTask_TurnToInterest::UBTTask_TurnToInterest()
{
    NodeName = TEXT("Turn To Interest");
    bNotifyTick = true;
}


EBTNodeResult::Type UBTTask_TurnToInterest::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    APawn* Pawn = AIController ? AIController->GetPawn() : nullptr;
    UBlackboardComponent* BB = AIController ? AIController->GetBlackboardComponent() : nullptr;

    if (!AIController || !Pawn || !BB) return EBTNodeResult::Failed;

    const FVector InterestLoc = BB->GetValueAsVector(InterestLocationKey.SelectedKeyName);
    if (InterestLoc.IsNearlyZero()) return EBTNodeResult::Succeeded; // 没有兴趣点，直接成功跳过

    FBTTask_TurnToInterestMemory* Memory = reinterpret_cast<FBTTask_TurnToInterestMemory*>(NodeMemory);

    // 停下并关闭随移动转向，避免与设定旋转冲突
    if (UCharacterMovementComponent* MoveComp = Pawn->FindComponentByClass<UCharacterMovementComponent>())
    {
        Memory->bCachedOrientRotationToMovement = MoveComp->bOrientRotationToMovement;
        Memory->bHasCachedMoveSetting = true;
        MoveComp->bOrientRotationToMovement = false;
        MoveComp->StopMovementImmediately();
    }
    AIController->StopMovement();

    const FVector ToTarget = (InterestLoc - Pawn->GetActorLocation()).GetSafeNormal2D();
    if (ToTarget.IsNearlyZero()) return EBTNodeResult::Succeeded;

    // 计算目标朝向
    Memory->TargetYaw = ToTarget.Rotation().Yaw;

    const float DeltaYaw = FMath::Abs(FMath::FindDeltaAngleDegrees(Pawn->GetActorRotation().Yaw, Memory->TargetYaw));
    if (DeltaYaw < MinTurnAngle)
    {
        // 角度很小，不必转身，直接放行
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::InProgress;
}

void UBTTask_TurnToInterest::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    APawn* Pawn = AIController ? AIController->GetPawn() : nullptr;
    UBlackboardComponent* BB = AIController ? AIController->GetBlackboardComponent() : nullptr;

    if (!Pawn || !BB)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    // 兴趣点消失（被 Clear）时中止，避免在空转
    if (!BB->GetValueAsBool(AEnemyAIController::BB_HasInterest))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    FBTTask_TurnToInterestMemory* Memory = reinterpret_cast<FBTTask_TurnToInterestMemory*>(NodeMemory);

    // 计算当前朝向与目标朝向的差值
    const float CurrentYaw = Pawn->GetActorRotation().Yaw;
    const float DeltaYaw   = FMath::FindDeltaAngleDegrees(CurrentYaw, Memory->TargetYaw);
    const float MaxStep    = TurnSpeed * DeltaSeconds;
    const float Step       = FMath::Clamp(DeltaYaw, -MaxStep, MaxStep);
    const float NewYaw     = FRotator::NormalizeAxis(CurrentYaw + Step);
    Pawn->SetActorRotation(FRotator(0.f, NewYaw, 0.f));

    // 检查是否到达目标朝向
    if (FMath::Abs(FMath::FindDeltaAngleDegrees(NewYaw, Memory->TargetYaw)) <= AcceptYawError)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}


void UBTTask_TurnToInterest::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
    Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

    AAIController* AIController = OwnerComp.GetAIOwner();
    APawn* Pawn = AIController ? AIController->GetPawn() : nullptr;
    FBTTask_TurnToInterestMemory* Memory = reinterpret_cast<FBTTask_TurnToInterestMemory*>(NodeMemory);
    
    // 恢复"随移动转向"，让后续 MoveTo 阶段可以边走边自然转向
    if (Pawn && Memory->bHasCachedMoveSetting)
    {
        if (UCharacterMovementComponent* MoveComp = Pawn->FindComponentByClass<UCharacterMovementComponent>())
        {
            MoveComp->bOrientRotationToMovement = Memory->bCachedOrientRotationToMovement;
        }
    }
}

uint16 UBTTask_TurnToInterest::GetInstanceMemorySize() const
{
    return sizeof(FBTTask_TurnToInterestMemory);
}