// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy/Enum/WaypointTypes.h"
#include "Components/SplineComponent.h"
#include "PatrolPath.generated.h"


/**
 * PatrolPath 是一种定义敌人巡逻路径的 Actor ，内含有多个巡逻点，敌人会按照这些巡逻点进行巡逻
 */

// 巡逻点行为类型(已移至 WaypointTypes.h)
// UENUM(BlueprintType)
// enum class EWaypointBehavior : uint8
// {
//     None        UMETA(DisplayName = "直接经过"),
//     LookAround  UMETA(DisplayName = "停下扫视"),
//     Wait        UMETA(DisplayName = "原地等待"),
// };

// 巡逻点绑定结构体
USTRUCT()
struct FWaypointBinding
{
    GENERATED_BODY()
    TWeakObjectPtr<AActor> Actor;
    FDelegateHandle TransformHandle;
};

// 巡逻点信息结构体
USTRUCT(BlueprintType)
struct FPatrolWaypointData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Point = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWaypointBehavior Behavior = EWaypointBehavior::None;

	// 停留时间
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WaitTime = 1.0f;

	// EWaypointBehavior 为 LookAround 时，激活
	// 扫视角度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Behavior == EWaypointBehavior::LookAround"))
	float LookAngle = 60.0f;

	// 扫视速度（度/秒）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Behavior == EWaypointBehavior::LookAround"))
	float LookSpeed = 80.0f;

	// ===== 扫视中轴线 =====

	// 是否使用自定义中轴线（以该节点箭头组件的朝向作为中轴线）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Behavior == EWaypointBehavior::LookAround"))
	bool bUseCustomLookCenter = false;

	// 中轴线目标（使用 ArrowActor 作为当前朝向点）
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Behavior == EWaypointBehavior::LookAround"))
	// AActor* LookCenterActor = nullptr;

	// 在中轴线基础上偏移（度）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Behavior == EWaypointBehavior::LookAround"))
	float LookCenterYawOffset = 0.0f;

	// 执行扫视时，静止多久（开启中轴线则为转到中轴线后）再开始左右转向
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta = (EditCondition = "Behavior == EWaypointBehavior::LookAround", ClampMin = "0.0", UIMin = "0.0", UIMax = "5.0"))
	float PreLookPauseTime = 0.5f;

};


UCLASS()
class INVISIBLE_API APatrolPath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatrolPath();

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 巡逻点数组
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
    TArray<FPatrolWaypointData> Waypoints;

    // 获取指定索引的巡逻点，越界时返回 nullptr
    AActor* GetWaypoint(int32 Index) const;

	// 获取完整路径点数据（供 BTTask 读取行为参数）
    FPatrolWaypointData GetWaypointData(int32 Index) const;
	
    // 巡逻点总数
    int32 Num() const { return Waypoints.Num(); }


	// 通过 Spline 绘制巡逻路径
	virtual void OnConstruction(const FTransform& Transform) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Patrol")
    USplineComponent* PatrolSpline = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol")
    bool bClosedLoop = false;


#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	void RebuildSplineFromWaypoints();


	void RebindWaypointEvents();

    void UnbindWaypointEvents();

    void QueueRebuild();

    void FlushQueuedRebuild();

    void HandleWaypointTransformUpdated(
        USceneComponent* UpdatedComponent,
        EUpdateTransformFlags UpdateTransformFlags,
        ETeleportType Teleport);


    UFUNCTION()
    void HandleWaypointDestroyed(AActor* DestroyedActor);

private:
    UPROPERTY()
    TArray<FWaypointBinding> WaypointBindings;
	
    bool bRebuildQueued = false;

};
