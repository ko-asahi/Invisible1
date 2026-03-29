// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BTTask_ClearInvestigateState.generated.h"

/**
 * MoveTo 后，清除运行时状态
 */
UCLASS()
class INVISIBLE_API UBTTask_ClearInvestigateState : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
    UBTTask_ClearInvestigateState();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
    UPROPERTY(EditAnywhere, Category="Blackboard")
    FBlackboardKeySelector HasInterestKey;

    UPROPERTY(EditAnywhere, Category="Blackboard")
    FBlackboardKeySelector IsInvestigatingKey;

    UPROPERTY(EditAnywhere, Category="Blackboard")
    FBlackboardKeySelector InterestLocationKey;

    UPROPERTY(EditAnywhere, Category="Blackboard")
    FBlackboardKeySelector HeardLocationKey;

    UPROPERTY(EditAnywhere, Category="Blackboard")
    FBlackboardKeySelector VisualTargetActorKey;

    UPROPERTY(EditAnywhere, Category="Blackboard")
    FBlackboardKeySelector IsChasingKey;

    UPROPERTY(EditAnywhere, Category="Blackboard")
    FBlackboardKeySelector AlertnessKey;

    UPROPERTY(EditAnywhere, Category="Options")
    bool bClearInterestLocation = true;

    UPROPERTY(EditAnywhere, Category="Options")
    bool bClearHeardLocation = false;

    UPROPERTY(EditAnywhere, Category="Options")
    bool bClearVisualTargetActor = true;
	
    UPROPERTY(EditAnywhere, Category="Options")
    bool bClearControllerRuntimeMemory = true;
};
