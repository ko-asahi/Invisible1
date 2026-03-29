// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BTTask_FaceTarget.generated.h"

/**
 * 实现角色面向目标的旋转功能
 */

// ai角色面向目标任务记忆结构体
struct FBTTask_FaceTargetMemory
{
	float TargetYaw = 0.f;	// 目标朝向
	bool bCachedOrientRotationToMovement = true; // 是否旋转到运动方向
	bool bHasCachedMoveSetting = false; // 是否移动
	//float ElapsedTime = 0.0f; // 持续时间
	float ElapsedTime = 0.0f; // 持续时间
};

UCLASS()
class INVISIBLE_API UBTTask_FaceTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_FaceTarget();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
	
	virtual uint16 GetInstanceMemorySize() const override;

private:
	// 实时视觉目标
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector VisualTargetActorKey;

	// 失去目标时，回退到最后目击点
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector LastSeenLocationKey;

	// 视角转动速度
	UPROPERTY(EditAnywhere, Category="Face")
	float TurnSpeed = 240.f; // 度/秒

	// 误差阈值（度）
	UPROPERTY(EditAnywhere, Category="Face")
	float AcceptYawError = 2.0f;

	// 看到或听到的首次位置
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector InterestLocationKey;

	// 看向持续时间（秒）
	UPROPERTY(EditAnywhere, Category = "Face", meta = (ClampMin = "0.0"))
	float FaceDuration = 2.0f;
	

	

	UPROPERTY(EditAnywhere, Category="Face")
	bool bTrackTargetDuringFace = false; // 持续期间是否实时跟踪目标
};
