// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Patrol.generated.h"

class AEnemyAIController;
class AEnemyBase;
class UBlackboardComponent;
struct FPatrolWaypointData;

/**
 * 沿 PatrolRouteProvider 样条连续巡逻，末端走回起点循环。
 * 绘制路径 / 交互接近由 EnemyAIController 的 InjectedPath 系统负责，本任务仅管样条。
 */
struct FBTTask_PatrolMemory
{
	float DistanceAlongRoute = 0.f;
	float RouteLength = 0.f;
	float CachedMaxWalkSpeed = -1.f;
	bool bReturningToStart = false;
};

UCLASS()
class INVISIBLE_API UBTTask_Patrol : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_Patrol();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

	virtual uint16 GetInstanceMemorySize() const override;

private:
	UPROPERTY(EditAnywhere, Category = "Patrol")
	float PatrolSpeedScale = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Patrol", meta=(ClampMin="5.0"))
	float ReturnToStartAcceptanceRadius = 60.0f;
};

