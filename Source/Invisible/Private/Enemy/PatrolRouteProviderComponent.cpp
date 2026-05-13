#include "Enemy/PatrolRouteProviderComponent.h"

#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include <limits>

// DEFINE_LOG_CATEGORY_STATIC(LogPatrolRouteProviderComp, Log, All);

UPatrolRouteProviderComponent::UPatrolRouteProviderComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UPatrolRouteProviderComponent::OnRegister()
{
    Super::OnRegister();
    // 避免每次注册/重编译时覆盖用户在详情面板里的行为编辑数据。
    // 需要同步长度时，手动点击 SyncBehaviorCountToSpline 按钮。
}

#if WITH_EDITOR
void UPatrolRouteProviderComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    // 避免编辑任意字段时触发长度同步导致行为数组被重置。
    // 如需同步，请手动调用 CallInEditor 按钮：SyncBehaviorCountToSpline。
}
#endif

void UPatrolRouteProviderComponent::SyncBehaviorCountToSpline()
{
    if (!bAutoSyncBehaviorCount)
    {
        return;
    }

    USplineComponent* Spline = ResolveSplineComponent();
    if (!Spline)
    {
        SplinePointBehaviors.Reset();
        return;
    }

    const int32 NumSplinePoints = Spline->GetNumberOfSplinePoints();
    if (NumSplinePoints <= 0)
    {
        SplinePointBehaviors.Reset();
        return;
    }

    SplinePointBehaviors.SetNum(NumSplinePoints);
}

void UPatrolRouteProviderComponent::GetProviderRoutePoints_Implementation(TArray<FVector>& OutPoints) const
{
    BuildRoutePoints(OutPoints);
}

int32 UPatrolRouteProviderComponent::GetProviderRoutePointCount_Implementation() const
{
    TArray<FVector> RoutePoints;
    BuildRoutePoints(RoutePoints);
    return RoutePoints.Num();
}

bool UPatrolRouteProviderComponent::GetProviderRoutePoint_Implementation(int32 Index, FVector& OutPoint) const
{
    TArray<FVector> RoutePoints;
    BuildRoutePoints(RoutePoints);
    if (!RoutePoints.IsValidIndex(Index))
    {
        return false;
    }

    OutPoint = RoutePoints[Index];
    return true;
}

void UPatrolRouteProviderComponent::GetProviderBehaviorDataForRoutePoint_Implementation(
    const FVector& RoutePointWorldLocation,
    EWaypointBehavior& OutBehavior,
    float& OutWaitTime,
    float& OutLookAngle,
    float& OutLookSpeed,
    bool& bOutUseCustomLookCenter,
    float& OutLookCenterYawOffset,
    float& OutPreLookPauseTime) const
{
    OutBehavior = EWaypointBehavior::None;
    OutWaitTime = 0.0f;
    OutLookAngle = 0.0f;
    OutLookSpeed = 0.0f;
    bOutUseCustomLookCenter = false;
    OutLookCenterYawOffset = 0.0f;
    OutPreLookPauseTime = 0.0f;

    int32 BestIndex = INDEX_NONE;
    float BestDistSq = 0.0f;
    if (!FindNearestSplinePoint(RoutePointWorldLocation, BestIndex, BestDistSq))
    {
        return;
    }

    const float AnchorRadius = FMath::Max(10.0f, BehaviorAnchorRadius);
    if (BestDistSq > FMath::Square(AnchorRadius))
    {
        return;
    }

    if (!SplinePointBehaviors.IsValidIndex(BestIndex))
    {
        return;
    }

    const FProviderSplineBehaviorData& Data = SplinePointBehaviors[BestIndex];
    OutBehavior = Data.Behavior;
    OutWaitTime = (Data.Behavior == EWaypointBehavior::Wait) ? Data.WaitTime : 0.0f;
    if (Data.Behavior == EWaypointBehavior::LookAround)
    {
        OutLookAngle = Data.LookAngle;
        OutLookSpeed = Data.LookSpeed;
        bOutUseCustomLookCenter = Data.bUseCustomLookCenter;
        OutLookCenterYawOffset = Data.LookCenterYawOffset;
        OutPreLookPauseTime = Data.PreLookPauseTime;
    }
}

bool UPatrolRouteProviderComponent::GetProviderBehaviorAnchorYawForRoutePoint_Implementation(const FVector& RoutePointWorldLocation, float& OutYaw) const
{
    const USplineComponent* Spline = ResolveSplineComponent();
    if (!Spline)
    {
        return false;
    }

    int32 BestIndex = INDEX_NONE;
    float BestDistSq = 0.0f;
    if (!FindNearestSplinePoint(RoutePointWorldLocation, BestIndex, BestDistSq))
    {
        return false;
    }

    const float AnchorRadius = FMath::Max(10.0f, BehaviorAnchorRadius);
    if (BestDistSq > FMath::Square(AnchorRadius))
    {
        return false;
    }

    OutYaw = Spline->GetRotationAtSplinePoint(BestIndex, ESplineCoordinateSpace::World).Yaw;
    return true;
}

bool UPatrolRouteProviderComponent::IsProviderClosedLoop_Implementation() const
{
    const USplineComponent* Spline = ResolveSplineComponent();
    return Spline ? Spline->IsClosedLoop() : false;
}

float UPatrolRouteProviderComponent::GetProviderRouteLength_Implementation() const
{
    const USplineComponent* Spline = ResolveSplineComponent();
    return Spline ? Spline->GetSplineLength() : 0.0f;
}

bool UPatrolRouteProviderComponent::GetProviderRouteTransformAtDistance_Implementation(float DistanceAlongRoute, FVector& OutLocation, FRotator& OutRotation) const
{
    const USplineComponent* Spline = ResolveSplineComponent();
    if (!Spline || Spline->GetNumberOfSplinePoints() <= 0)
    {
        return false;
    }

    const float SplineLength = Spline->GetSplineLength();
    if (SplineLength <= KINDA_SMALL_NUMBER)
    {
        OutLocation = Spline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
        OutRotation = Spline->GetRotationAtSplinePoint(0, ESplineCoordinateSpace::World);
        return true;
    }

    const float ClampedDistance = FMath::Clamp(DistanceAlongRoute, 0.0f, SplineLength);
    OutLocation = Spline->GetLocationAtDistanceAlongSpline(ClampedDistance, ESplineCoordinateSpace::World);
    OutRotation = Spline->GetRotationAtDistanceAlongSpline(ClampedDistance, ESplineCoordinateSpace::World);
    return true;
}

bool UPatrolRouteProviderComponent::ProjectWorldLocationToRouteDistance_Implementation(const FVector& WorldLocation, float& OutDistanceAlongRoute) const
{
    const USplineComponent* Spline = ResolveSplineComponent();
    if (!Spline || Spline->GetNumberOfSplinePoints() <= 0)
    {
        return false;
    }

    const float InputKey = Spline->FindInputKeyClosestToWorldLocation(WorldLocation);
    OutDistanceAlongRoute = Spline->GetDistanceAlongSplineAtSplineInputKey(InputKey);
    return true;
}

bool UPatrolRouteProviderComponent::GetNearestSplineControlPointIndex_Implementation(const FVector& WorldLocation, int32& OutIndex, float& OutDistSq) const
{
    return FindNearestSplinePoint(WorldLocation, OutIndex, OutDistSq);
}

void UPatrolRouteProviderComponent::BuildRoutePoints(TArray<FVector>& OutPoints) const
{
    OutPoints.Reset();

    const USplineComponent* Spline = ResolveSplineComponent();
    if (!Spline)
    {
        return;
    }

    const int32 NumSplinePoints = Spline->GetNumberOfSplinePoints();
    if (NumSplinePoints <= 0)
    {
        return;
    }

    OutPoints.Reserve(NumSplinePoints);
    for (int32 PointIndex = 0; PointIndex < NumSplinePoints; ++PointIndex)
    {
        OutPoints.Add(Spline->GetLocationAtSplinePoint(PointIndex, ESplineCoordinateSpace::World));
    }
}

USplineComponent* UPatrolRouteProviderComponent::ResolveSplineComponent() const
{
    AActor* Owner = GetOwner();
    if (!Owner)
    {
        // UE_LOG(LogPatrolRouteProviderComp, Warning, TEXT("[PatrolRouteProviderComponent] Owner is null."));
        return nullptr;
    }

    if (!SplineComponentName.IsNone())
    {
        TInlineComponentArray<USplineComponent*> SplineComponents(Owner);
        for (USplineComponent* Comp : SplineComponents)
        {
            if (Comp && Comp->GetFName() == SplineComponentName)
            {
                return Comp;
            }
        }

        // UE_LOG(LogPatrolRouteProviderComp, Warning, TEXT("[%s] SplineComponentName '%s' not found."), *GetNameSafe(Owner), *SplineComponentName.ToString());
    }

    TInlineComponentArray<USplineComponent*> SplineComponents(Owner);
    USplineComponent* BestSpline = nullptr;
    int32 BestPoints = -1;
    for (USplineComponent* Comp : SplineComponents)
    {
        if (!Comp)
        {
            continue;
        }

        const int32 NumPoints = Comp->GetNumberOfSplinePoints();
        if (NumPoints > BestPoints)
        {
            BestPoints = NumPoints;
            BestSpline = Comp;
        }
    }

    if (!BestSpline)
    {
        // UE_LOG(LogPatrolRouteProviderComp, Warning, TEXT("[%s] No USplineComponent found on provider actor."), *GetNameSafe(Owner));
    }

    return BestSpline;
}

bool UPatrolRouteProviderComponent::FindNearestSplinePoint(const FVector& RoutePointWorldLocation, int32& OutIndex, float& OutDistSq) const
{
    const USplineComponent* Spline = ResolveSplineComponent();
    if (!Spline || Spline->GetNumberOfSplinePoints() <= 0)
    {
        return false;
    }

    const int32 NumPoints = Spline->GetNumberOfSplinePoints();
    OutIndex = INDEX_NONE;
    OutDistSq = TNumericLimits<float>::Max();
    for (int32 i = 0; i < NumPoints; ++i)
    {
        const FVector Point = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
        const float DistSq = FVector::DistSquared(RoutePointWorldLocation, Point);
        if (DistSq < OutDistSq)
        {
            OutDistSq = DistSq;
            OutIndex = i;
        }
    }

    return OutIndex != INDEX_NONE;
}

