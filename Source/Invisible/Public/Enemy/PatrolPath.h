// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy/Enum/WaypointTypes.h"
#include "Enemy/PatrolRouteProvider.h"
#include "Components/SplineComponent.h"
#include "PatrolPath.generated.h"

class USceneComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPatrolPathChanged);


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

// 样条控制点行为数据（方案1：样条即路径源）
USTRUCT(BlueprintType)
struct FSplinePatrolBehaviorData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EWaypointBehavior Behavior = EWaypointBehavior::None;

    // 停留时间
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WaitTime = 1.0f;

    // EWaypointBehavior 为 LookAround 时，激活
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Behavior == EWaypointBehavior::LookAround"))
    float LookAngle = 60.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Behavior == EWaypointBehavior::LookAround"))
    float LookSpeed = 80.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Behavior == EWaypointBehavior::LookAround"))
    bool bUseCustomLookCenter = false;

    // 在样条控制点旋转基础上偏移（度）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Behavior == EWaypointBehavior::LookAround"))
    float LookCenterYawOffset = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Behavior == EWaypointBehavior::LookAround", ClampMin = "0.0", UIMin = "0.0", UIMax = "5.0"))
    float PreLookPauseTime = 0.5f;
};


UCLASS()
class INVISIBLE_API APatrolPath : public AActor, public IPatrolRouteProvider
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

    // 路径发生变化时广播（样条点、闭环、行为配置等）
    UPROPERTY(BlueprintAssignable, Category="Patrol|Events")
    FOnPatrolPathChanged OnPathChanged;

    // ===== PatrolRouteProvider 接口 =====
    virtual void GetProviderRoutePoints_Implementation(TArray<FVector>& OutPoints) const override;
    virtual int32 GetProviderRoutePointCount_Implementation() const override;
    virtual bool GetProviderRoutePoint_Implementation(int32 Index, FVector& OutPoint) const override;
    virtual void GetProviderBehaviorDataForRoutePoint_Implementation(
        const FVector& RoutePointWorldLocation,
        EWaypointBehavior& OutBehavior,
        float& OutWaitTime,
        float& OutLookAngle,
        float& OutLookSpeed,
        bool& bOutUseCustomLookCenter,
        float& OutLookCenterYawOffset,
        float& OutPreLookPauseTime) const override;
    virtual bool GetProviderBehaviorAnchorYawForRoutePoint_Implementation(const FVector& RoutePointWorldLocation, float& OutYaw) const override;
    virtual bool IsProviderClosedLoop_Implementation() const override;
    virtual float GetProviderRouteLength_Implementation() const override;
    virtual bool GetProviderRouteTransformAtDistance_Implementation(float DistanceAlongRoute, FVector& OutLocation, FRotator& OutRotation) const override;
    virtual bool ProjectWorldLocationToRouteDistance_Implementation(const FVector& WorldLocation, float& OutDistanceAlongRoute) const override;
    virtual bool GetNearestSplineControlPointIndex_Implementation(const FVector& WorldLocation, int32& OutIndex, float& OutDistSq) const override;

	// 巡逻点数组
    // 旧模式数据：当 bSplineAsPathSource=false 时使用
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
    TArray<FPatrolWaypointData> Waypoints;

    // 获取指定索引的巡逻点，越界时返回 nullptr
    AActor* GetWaypoint(int32 Index) const;

	// 获取完整路径点数据（供 BTTask 读取行为参数）
    FPatrolWaypointData GetWaypointData(int32 Index) const;
	
    // 巡逻点总数
    int32 Num() const { return Waypoints.Num(); }

    // 是否使用样条作为路径真源（方案1）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol|Spline")
    bool bSplineAsPathSource = true;

    // 已弃用：旧采样方案参数。当前巡逻直接使用样条控制点，不再按距离采样。
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol|Spline", meta=(DeprecatedProperty, DeprecationMessage="SplineSampleInterval 已弃用，巡逻点直接使用样条控制点。", ClampMin="50.0", UIMin="50.0", UIMax="500.0"))
    float SplineSampleInterval = 180.0f;

    // 巡逻执行点距离某个行为锚点小于该值时，触发该点行为
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol|Spline", meta=(ClampMin="10.0", UIMin="10.0", UIMax="300.0"))
    float BehaviorAnchorRadius = 80.0f;

    // 样条控制点行为配置（索引与样条点一一对应）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol|Spline")
    TArray<FSplinePatrolBehaviorData> SplinePointBehaviors;

    // 自动同步行为数组长度到样条点数
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol|Spline")
    bool bAutoSyncSplineBehaviorCount = true;

    // 获取用于巡逻执行的路径点（样条模式使用控制点，旧模式使用 Waypoints）
    UFUNCTION(BlueprintCallable, Category="Patrol")
    void GetPatrolRoutePoints(TArray<FVector>& OutPoints) const;

    // 获取转换到指定组件本地坐标系的巡逻路径点（用于 ProceduralMesh 等组件）
    UFUNCTION(BlueprintCallable, Category="Patrol")
    void GetPatrolRoutePointsLocalToComponent(const USceneComponent* TargetComponent, TArray<FVector>& OutPointsLocal) const;

    // 获取巡逻执行路径点总数
    UFUNCTION(BlueprintPure, Category="Patrol")
    int32 GetPatrolRoutePointCount() const;

    // 获取巡逻执行路径中的指定点
    UFUNCTION(BlueprintCallable, Category="Patrol")
    bool GetPatrolRoutePoint(int32 Index, FVector& OutPoint) const;

    // 根据巡逻执行点位置，解析该点应触发的行为数据（非锚点返回 None）
    UFUNCTION(BlueprintCallable, Category="Patrol")
    FPatrolWaypointData GetBehaviorDataForRoutePoint(const FVector& RoutePointWorldLocation) const;

    // 获取巡逻执行点对应的样条控制点中轴线朝向（用于 LookAround）
    UFUNCTION(BlueprintCallable, Category="Patrol")
    bool GetBehaviorAnchorYawForRoutePoint(const FVector& RoutePointWorldLocation, float& OutYaw) const;


	// 通过 Spline 绘制巡逻路径
	virtual void OnConstruction(const FTransform& Transform) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Patrol")
    USplineComponent* PatrolSpline = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol")
    bool bClosedLoop = false;

    // 蓝图读取巡逻路径是否闭环（避免直接读属性时反射缓存问题）
    UFUNCTION(BlueprintPure, Category="Patrol")
    bool IsPatrolClosedLoop() const { return bClosedLoop; }


#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	void RebuildSplineFromWaypoints();
    void EnsureSplineBehaviorCount();
    void BroadcastPathChanged();


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
