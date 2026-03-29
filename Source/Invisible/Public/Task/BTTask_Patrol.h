// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Patrol.generated.h"

/**
 * 实现角色巡逻功能
 */
struct FBTTask_PatrolMemory
{
	FDelegateHandle MoveCompletedHandle;	// 移动完成回调句柄
	FAIRequestID CurrentRequestID;		// 当前请求ID
};

UCLASS()
class INVISIBLE_API UBTTask_Patrol : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_Patrol();

	// 巡逻事件驱动执行
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// 每帧检测 HasInterest，出现兴趣点时立刻中止移动
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	// 任务结束时清理绑定（成功/失败/中止均会调用）
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

	virtual uint16 GetInstanceMemorySize() const override;

private:
	// 到达巡逻点的接受半径
	UPROPERTY(EditAnywhere, Category = "Patrol")
	float AcceptanceRadius = 50.0f;

	

	
	
};


