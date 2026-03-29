// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_LookAround.generated.h"

/**
 * ai角色扫视任务
 */


struct FBTTask_LookAroundMemory
{
	float InitialYaw;	// 初始朝向
	float TargetYaw;	// 当前目标朝向
	int32 Phase;		// 下一步转向方向，0=转中轴, 1=中轴静止, 2=左, 3=右, 4=回中轴
	float CenterYaw;    // 中轴线朝向
	float WaitBeforeSweepRemaining;    // 等待计时
};


UCLASS()
class INVISIBLE_API UBTTask_LookAround : public UBTTaskNode
{
	GENERATED_BODY()

	
public:
	UBTTask_LookAround();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
    virtual uint16 GetInstanceMemorySize() const override;
};
