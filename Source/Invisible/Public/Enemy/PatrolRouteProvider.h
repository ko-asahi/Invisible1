#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enemy/Enum/WaypointTypes.h"
#include "PatrolRouteProvider.generated.h"

UINTERFACE(BlueprintType)
class INVISIBLE_API UPatrolRouteProvider : public UInterface
{
    GENERATED_BODY()
};

class INVISIBLE_API IPatrolRouteProvider
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Patrol|Route")
    void GetProviderRoutePoints(TArray<FVector>& OutPoints) const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Patrol|Route")
    int32 GetProviderRoutePointCount() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Patrol|Route")
    bool GetProviderRoutePoint(int32 Index, FVector& OutPoint) const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Patrol|Route")
    void GetProviderBehaviorDataForRoutePoint(
        const FVector& RoutePointWorldLocation,
        EWaypointBehavior& OutBehavior,
        float& OutWaitTime,
        float& OutLookAngle,
        float& OutLookSpeed,
        bool& bOutUseCustomLookCenter,
        float& OutLookCenterYawOffset,
        float& OutPreLookPauseTime) const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Patrol|Route")
    bool GetProviderBehaviorAnchorYawForRoutePoint(const FVector& RoutePointWorldLocation, float& OutYaw) const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Patrol|Route")
    bool IsProviderClosedLoop() const;

    // 获取巡逻路径总长度（样条模式）
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Patrol|Route")
    float GetProviderRouteLength() const;

    // 按路径距离获取位置与朝向（样条模式）
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Patrol|Route")
    bool GetProviderRouteTransformAtDistance(float DistanceAlongRoute, FVector& OutLocation, FRotator& OutRotation) const;

    // 将世界坐标投影到路径距离（样条模式）
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Patrol|Route")
    bool ProjectWorldLocationToRouteDistance(const FVector& WorldLocation, float& OutDistanceAlongRoute) const;

    // 最近样条控制点索引（用于巡逻行为锚点冷却等）
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Patrol|Route")
    bool GetNearestSplineControlPointIndex(const FVector& WorldLocation, int32& OutIndex, float& OutDistSq) const;
};
