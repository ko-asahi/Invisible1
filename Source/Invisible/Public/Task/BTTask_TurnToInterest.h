// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BTTask_TurnToInterest.generated.h"

/**
 * BTTask_TurnToInterest用于在AI走向兴趣点前，让AI转身，面向兴趣点
 */

// 转身任务记忆结构体
struct FBTTask_TurnToInterestMemory
{
    float TargetYaw = 0.0f;	// 目标朝向
    bool bCachedOrientRotationToMovement = true; // 是否缓存旋转到运动方向
    bool bHasCachedMoveSetting = false; // 是否缓存移动设置
};

UCLASS()
class INVISIBLE_API UBTTask_TurnToInterest : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
    UBTTask_TurnToInterest();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
    virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
    virtual uint16 GetInstanceMemorySize() const override;
private:
    // 读取兴趣点位置的黑板键
    UPROPERTY(EditAnywhere, Category="Blackboard")
    FBlackboardKeySelector InterestLocationKey;

    // 小于该角度就不做预转身，直接成功
    UPROPERTY(EditAnywhere, Category="Turn")
    float MinTurnAngle = 5.0f;

    // 原地转向速度（度/秒）
    UPROPERTY(EditAnywhere, Category="Turn")
    float TurnSpeed = 240.0f;

    // 误差阈值（度）
    UPROPERTY(EditAnywhere, Category="Turn")
    float AcceptYawError = 2.0f;
};
