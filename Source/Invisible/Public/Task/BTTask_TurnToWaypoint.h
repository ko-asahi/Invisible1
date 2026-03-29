// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TurnToWaypoint.generated.h"

/**
 * 实现角色在路径点处转身的功能
 */

// 转身任务记忆结构体
struct FBTTask_TurnToWaypointMemory
{

	float TargetYaw = 0.0f;	// 目标朝向
	bool bCachedOrientRotationToMovement = true; // 是否缓存旋转到运动方向
	bool bHasCachedMoveSetting = false; // 是否缓存移动设置
};

UCLASS()
class INVISIBLE_API UBTTask_TurnToWaypoint : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_TurnToWaypoint();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
	virtual uint16 GetInstanceMemorySize() const override;

private:
	// 小于该角度就不做预转身，直接成功
	UPROPERTY(EditAnywhere, Category = "Turn")
	float MinTurnAngle = 12.0f;

	// 原地转向速度（度/秒）
	UPROPERTY(EditAnywhere, Category = "Turn")
	float TurnSpeed = 180.0f;

	// 误差阈值（度）
	UPROPERTY(EditAnywhere, Category = "Turn")
	float AcceptYawError = 2.0f;
	
};
