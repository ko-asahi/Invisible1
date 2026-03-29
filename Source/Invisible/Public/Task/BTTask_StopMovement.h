// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_StopMovement.generated.h"

/**
 * 角色停止移动事件
 */
UCLASS()
class INVISIBLE_API UBTTask_StopMovement : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_StopMovement();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
