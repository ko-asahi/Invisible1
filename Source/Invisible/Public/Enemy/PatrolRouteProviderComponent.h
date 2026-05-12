#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enemy/Enum/WaypointTypes.h"
#include "Enemy/PatrolRouteProvider.h"
#include "PatrolRouteProviderComponent.generated.h"

class USplineComponent;

USTRUCT(BlueprintType)
struct FProviderSplineBehaviorData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol")
    EWaypointBehavior Behavior = EWaypointBehavior::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol")
    float WaitTime = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol", meta=(EditCondition="Behavior == EWaypointBehavior::LookAround"))
    float LookAngle = 60.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol", meta=(EditCondition="Behavior == EWaypointBehavior::LookAround"))
    float LookSpeed = 80.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol", meta=(EditCondition="Behavior == EWaypointBehavior::LookAround"))
    bool bUseCustomLookCenter = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol", meta=(EditCondition="Behavior == EWaypointBehavior::LookAround"))
    float LookCenterYawOffset = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol", meta=(EditCondition="Behavior == EWaypointBehavior::LookAround", ClampMin="0.0", UIMin="0.0", UIMax="5.0"))
    float PreLookPauseTime = 0.5f;
};

UCLASS(ClassGroup=(AI), meta=(BlueprintSpawnableComponent))
class INVISIBLE_API UPatrolRouteProviderComponent : public UActorComponent, public IPatrolRouteProvider
{
    GENERATED_BODY()

public:
    UPatrolRouteProviderComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol")
    FName SplineComponentName = NAME_None;

    // 已弃用：旧采样方案参数。当前巡逻直接使用样条控制点，不再按距离采样。
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol", meta=(DeprecatedProperty, DeprecationMessage="SampleInterval 已弃用，巡逻点直接使用样条控制点。", ClampMin="50.0", UIMin="50.0", UIMax="500.0"))
    float SampleInterval = 180.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol", meta=(ClampMin="10.0", UIMin="10.0", UIMax="300.0"))
    float BehaviorAnchorRadius = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol")
    bool bAutoSyncBehaviorCount = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol")
    TArray<FProviderSplineBehaviorData> SplinePointBehaviors;

    UFUNCTION(BlueprintCallable, CallInEditor, Category="Patrol")
    void SyncBehaviorCountToSpline();

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

protected:
    virtual void OnRegister() override;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
    void BuildRoutePoints(TArray<FVector>& OutPoints) const;
    USplineComponent* ResolveSplineComponent() const;
    bool FindNearestSplinePoint(const FVector& RoutePointWorldLocation, int32& OutIndex, float& OutDistSq) const;
};

