// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTask_StopMovement.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Pawn.h"

UBTTask_StopMovement::UBTTask_StopMovement()
{
	NodeName = TEXT("Stop Movement");
}

EBTNodeResult::Type UBTTask_StopMovement::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
    if(AIController)
    {
        AIController->StopMovement();
        if(APawn* Pawn = AIController->GetPawn())
        {
            if(UCharacterMovementComponent* MoveComp = Cast<UCharacterMovementComponent>(Pawn->GetComponentByClass(UCharacterMovementComponent::StaticClass())))
            {
                MoveComp->StopMovementImmediately();
            }
        }
        return EBTNodeResult::Succeeded;
    }
	return EBTNodeResult::Failed;
}

