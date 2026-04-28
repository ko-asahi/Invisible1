// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTask_ClearInvestigateState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/EnemyAIController.h"


UBTTask_ClearInvestigateState::UBTTask_ClearInvestigateState()
{
    NodeName = TEXT("Clear Investigate State");
}

EBTNodeResult::Type UBTTask_ClearInvestigateState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
    if (!BB)
    {
        return EBTNodeResult::Failed;
    }

    // 基础状态清理
    BB->SetValueAsBool(HasInterestKey.SelectedKeyName, false);
    BB->SetValueAsBool(IsInvestigatingKey.SelectedKeyName, false);

    if (bClearInterestLocation)
    {
        BB->ClearValue(InterestLocationKey.SelectedKeyName);
    }

    if (bClearHeardLocation)
    {
        BB->ClearValue(HeardLocationKey.SelectedKeyName);
    }

    if (bClearVisualTargetActor)
    {
        BB->ClearValue(VisualTargetActorKey.SelectedKeyName);
    }

    if (bClearControllerRuntimeMemory)
    {
        if (AEnemyAIController* EnemyAI = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()))
        {
            EnemyAI->ClearInvestigateRuntimeState(true);
        }
    }

    if (bResetChasingOnClear)
    {
        BB->SetValueAsBool(IsChasingKey.SelectedKeyName, false);
    }
    if (bResetAlertnessOnClear)
    {
        BB->SetValueAsFloat(AlertnessKey.SelectedKeyName, 0.0f);
    }

    return EBTNodeResult::Succeeded;
}