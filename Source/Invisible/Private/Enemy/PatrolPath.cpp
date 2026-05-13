// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/PatrolPath.h"
#include "DrawDebugHelpers.h"
#include "Components/SceneComponent.h"
#include <limits>

/**
 * PatrolPath 是一种定义敌人巡逻路径的 Actor ，内含有多个巡逻点，敌人会按照这些巡逻点进行巡逻
 */

// Sets default values
APatrolPath::APatrolPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;  // 不依赖 Tick 画线，改用 Spline 组件

    PatrolSpline = CreateDefaultSubobject<USplineComponent>(TEXT("PatrolSpline"));
    RootComponent = PatrolSpline;
    //PatrolSpline->SetClosedLoop(true);

    PatrolSpline->SetDrawDebug(true);


}



// Called when the game starts or when spawned
void APatrolPath::BeginPlay()
{
	Super::BeginPlay();

    if (bSplineAsPathSource)
    {
        if (PatrolSpline)
        {
            PatrolSpline->SetClosedLoop(bClosedLoop, false);
            PatrolSpline->UpdateSpline();
        }
        EnsureSplineBehaviorCount();
    }
    else
    {
        // 绑定路径点修改事件
        RebindWaypointEvents();
        // 重建样条线
        RebuildSplineFromWaypoints();
    }

    BroadcastPathChanged();
}

void APatrolPath::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (!bSplineAsPathSource)
    {
        // 解绑路径点修改事件
        UnbindWaypointEvents();
    }

    Super::EndPlay(EndPlayReason);
}

// Called every frame
void APatrolPath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

     
    

// 在开发和调试时显示巡逻路径（旧方案）
// #if ENABLE_DRAW_DEBUG
// 	for(int32 i = 0; i < Waypoints.Num(); i++)
// 	{
// 		if (!Waypoints[i].Point) continue;
// 		FVector Loc = Waypoints[i].Point->GetActorLocation();

// 		FColor Color = (Waypoints[i].Behavior == EWaypointBehavior::None) ? FColor::Cyan : FColor::Yellow;
//         DrawDebugSphere(GetWorld(), Loc, 30.f, 12, Color, false, -1.f);
//         DrawDebugString(GetWorld(), Loc + FVector(0, 0, 60),
//             FString::Printf(TEXT("[%d] %s"), i,
//                 *UEnum::GetValueAsString(Waypoints[i].Behavior)),
//             nullptr, FColor::White, -1.f);
//         if (i > 0 && Waypoints[i - 1].Point)
//             DrawDebugLine(GetWorld(),
//                 Waypoints[i - 1].Point->GetActorLocation(), Loc,
//                 Color, false, -1.f, 0, 2.f);
//     }
// #endif
}


// 获取指定索引巡逻点
AActor* APatrolPath::GetWaypoint(int32 Index) const
{
	if (Waypoints.IsEmpty() || Index < 0 || !Waypoints.IsValidIndex(Index)) return nullptr;
    return Waypoints[Index].Point;
}

// 获取完整路径点数据（供 BTTask 读取行为参数）
FPatrolWaypointData APatrolPath::GetWaypointData(int32 Index) const
{
    if (!Waypoints.IsValidIndex(Index)) return FPatrolWaypointData();
    return Waypoints[Index];
}

void APatrolPath::GetPatrolRoutePoints(TArray<FVector>& OutPoints) const
{
    OutPoints.Reset();

    if (PatrolSpline)
    {
        const int32 NumSplinePoints = PatrolSpline->GetNumberOfSplinePoints();
        if (NumSplinePoints <= 0)
        {
            return;
        }

        OutPoints.Reserve(NumSplinePoints);
        for (int32 PointIndex = 0; PointIndex < NumSplinePoints; ++PointIndex)
        {
            OutPoints.Add(PatrolSpline->GetLocationAtSplinePoint(PointIndex, ESplineCoordinateSpace::World));
        }
        return;
    }

    // 回退模式：样条点不足时用旧路径点
    for (const FPatrolWaypointData& WP : Waypoints)
    {
        if (IsValid(WP.Point))
        {
            OutPoints.Add(WP.Point->GetActorLocation());
        }
    }
}

void APatrolPath::GetPatrolRoutePointsLocalToComponent(const USceneComponent* TargetComponent, TArray<FVector>& OutPointsLocal) const
{
    TArray<FVector> RoutePointsWorld;
    GetPatrolRoutePoints(RoutePointsWorld);

    OutPointsLocal.Reset();
    if (RoutePointsWorld.IsEmpty())
    {
        return;
    }

    // 若未提供目标组件，回退输出世界坐标，避免蓝图端出现空数组导致流程中断
    if (!IsValid(TargetComponent))
    {
        OutPointsLocal = RoutePointsWorld;
        return;
    }

    const FTransform TargetTransform = TargetComponent->GetComponentTransform();
    OutPointsLocal.Reserve(RoutePointsWorld.Num());
    for (const FVector& WorldPoint : RoutePointsWorld)
    {
        OutPointsLocal.Add(TargetTransform.InverseTransformPosition(WorldPoint));
    }
}

int32 APatrolPath::GetPatrolRoutePointCount() const
{
    TArray<FVector> RoutePoints;
    GetPatrolRoutePoints(RoutePoints);
    return RoutePoints.Num();
}

bool APatrolPath::GetPatrolRoutePoint(int32 Index, FVector& OutPoint) const
{
    TArray<FVector> RoutePoints;
    GetPatrolRoutePoints(RoutePoints);
    if (!RoutePoints.IsValidIndex(Index))
    {
        return false;
    }

    OutPoint = RoutePoints[Index];
    return true;
}

FPatrolWaypointData APatrolPath::GetBehaviorDataForRoutePoint(const FVector& RoutePointWorldLocation) const
{
    FPatrolWaypointData Result;
    Result.Behavior = EWaypointBehavior::None;
    Result.WaitTime = 0.0f;

    if (bSplineAsPathSource && PatrolSpline && PatrolSpline->GetNumberOfSplinePoints() > 0)
    {
        const int32 NumSplinePoints = PatrolSpline->GetNumberOfSplinePoints();
        float BestDistSq = TNumericLimits<float>::Max();
        int32 BestIndex = INDEX_NONE;

        for (int32 i = 0; i < NumSplinePoints; ++i)
        {
            const FVector AnchorLoc = PatrolSpline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
            const float DistSq = FVector::DistSquared(RoutePointWorldLocation, AnchorLoc);
            if (DistSq < BestDistSq)
            {
                BestDistSq = DistSq;
                BestIndex = i;
            }
        }

        if (BestIndex == INDEX_NONE || !SplinePointBehaviors.IsValidIndex(BestIndex))
        {
            return Result;
        }

        const float AnchorRadius = FMath::Max(10.0f, BehaviorAnchorRadius);
        if (BestDistSq > FMath::Square(AnchorRadius))
        {
            return Result;
        }

        const FSplinePatrolBehaviorData& BehaviorData = SplinePointBehaviors[BestIndex];
        Result.Point = nullptr;
        Result.Behavior = BehaviorData.Behavior;
        Result.WaitTime = (BehaviorData.Behavior == EWaypointBehavior::Wait) ? BehaviorData.WaitTime : 0.0f;
        if (BehaviorData.Behavior == EWaypointBehavior::LookAround)
        {
            Result.LookAngle = BehaviorData.LookAngle;
            Result.LookSpeed = BehaviorData.LookSpeed;
            Result.bUseCustomLookCenter = BehaviorData.bUseCustomLookCenter;
            Result.LookCenterYawOffset = BehaviorData.LookCenterYawOffset;
            Result.PreLookPauseTime = BehaviorData.PreLookPauseTime;
        }
        else
        {
            Result.LookAngle = 0.0f;
            Result.LookSpeed = 0.0f;
            Result.bUseCustomLookCenter = false;
            Result.LookCenterYawOffset = 0.0f;
            Result.PreLookPauseTime = 0.0f;
        }
        return Result;
    }

    float BestDistSq = TNumericLimits<float>::Max();
    int32 BestIndex = INDEX_NONE;
    for (int32 i = 0; i < Waypoints.Num(); ++i)
    {
        const FPatrolWaypointData& WP = Waypoints[i];
        if (!IsValid(WP.Point))
        {
            continue;
        }

        const float DistSq = FVector::DistSquared(RoutePointWorldLocation, WP.Point->GetActorLocation());
        if (DistSq < BestDistSq)
        {
            BestDistSq = DistSq;
            BestIndex = i;
        }
    }

    if (BestIndex == INDEX_NONE)
    {
        return Result;
    }

    const float AnchorRadius = FMath::Max(10.0f, BehaviorAnchorRadius);
    if (BestDistSq <= FMath::Square(AnchorRadius))
    {
        return Waypoints[BestIndex];
    }

    return Result;
}

bool APatrolPath::GetBehaviorAnchorYawForRoutePoint(const FVector& RoutePointWorldLocation, float& OutYaw) const
{
    if (!PatrolSpline || PatrolSpline->GetNumberOfSplinePoints() <= 0)
    {
        return false;
    }

    const int32 NumSplinePoints = PatrolSpline->GetNumberOfSplinePoints();
    float BestDistSq = TNumericLimits<float>::Max();
    int32 BestIndex = INDEX_NONE;

    for (int32 i = 0; i < NumSplinePoints; ++i)
    {
        const FVector AnchorLoc = PatrolSpline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
        const float DistSq = FVector::DistSquared(RoutePointWorldLocation, AnchorLoc);
        if (DistSq < BestDistSq)
        {
            BestDistSq = DistSq;
            BestIndex = i;
        }
    }

    if (BestIndex == INDEX_NONE)
    {
        return false;
    }

    const float AnchorRadius = FMath::Max(10.0f, BehaviorAnchorRadius);
    if (BestDistSq > FMath::Square(AnchorRadius))
    {
        return false;
    }

    OutYaw = PatrolSpline->GetRotationAtSplinePoint(BestIndex, ESplineCoordinateSpace::World).Yaw;
    return true;
}

// 通过 Spline 绘制巡逻路径
void APatrolPath::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (bSplineAsPathSource)
    {
        if (PatrolSpline)
        {
            PatrolSpline->SetClosedLoop(bClosedLoop, false);
            PatrolSpline->UpdateSpline();
        }
        EnsureSplineBehaviorCount();
    }
    else
    {
        // 绑定路径点修改事件
        RebindWaypointEvents();
        // 重建样条线
        RebuildSplineFromWaypoints();
    }

    BroadcastPathChanged();
}

// 从 Waypoints 重新构建 Spline 路径
void APatrolPath::RebuildSplineFromWaypoints()
{
    if (!PatrolSpline) return;

    PatrolSpline->ClearSplinePoints(false);
    
    for (const FPatrolWaypointData& WP : Waypoints)
    {
        if (!WP.Point) continue;

        const FVector WorldLoc = WP.Point->GetActorLocation();
        const FVector LocalLoc = GetActorTransform().InverseTransformPosition(WorldLoc);

        PatrolSpline->AddSplinePoint(LocalLoc, ESplineCoordinateSpace::Local, false);
    }

    PatrolSpline->SetClosedLoop(bClosedLoop, false);

    for (int32 i = 0; i < PatrolSpline->GetNumberOfSplinePoints(); ++i)
    {
        PatrolSpline->SetSplinePointType(i, ESplinePointType::Curve, false);
    }

    PatrolSpline->UpdateSpline();
}

// =====事件驱动实现样条线实时绘制=====

#if WITH_EDITOR
void APatrolPath::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    // Waypoints / bClosedLoop 被改时触发重绑+重建
    static const FName WaypointsName = GET_MEMBER_NAME_CHECKED(APatrolPath, Waypoints);
    static const FName ClosedLoopName = GET_MEMBER_NAME_CHECKED(APatrolPath, bClosedLoop);
    static const FName SplineSourceName = GET_MEMBER_NAME_CHECKED(APatrolPath, bSplineAsPathSource);
    static const FName AnchorRadiusName = GET_MEMBER_NAME_CHECKED(APatrolPath, BehaviorAnchorRadius);
    static const FName SplineBehaviorName = GET_MEMBER_NAME_CHECKED(APatrolPath, SplinePointBehaviors);
    static const FName AutoSyncName = GET_MEMBER_NAME_CHECKED(APatrolPath, bAutoSyncSplineBehaviorCount);

    const FName Changed = PropertyChangedEvent.GetPropertyName();
    if (Changed == SplineSourceName || Changed == ClosedLoopName)
    {
        if (bSplineAsPathSource)
        {
            UnbindWaypointEvents();
            if (PatrolSpline)
            {
                PatrolSpline->SetClosedLoop(bClosedLoop, false);
                PatrolSpline->UpdateSpline();
            }
            EnsureSplineBehaviorCount();
        }
        else
        {
            RebindWaypointEvents();
            QueueRebuild();
        }
        BroadcastPathChanged();
        return;
    }

    if (Changed == AnchorRadiusName || Changed == SplineBehaviorName || Changed == AutoSyncName)
    {
        EnsureSplineBehaviorCount();
        BroadcastPathChanged();
        return;
    }

    if (bSplineAsPathSource)
    {
        EnsureSplineBehaviorCount();
        BroadcastPathChanged();
        return;
    }

    if (Changed == WaypointsName)
    {
        RebindWaypointEvents();
        QueueRebuild();
        BroadcastPathChanged();
    }
}
#endif


// 绑定路径点修改事件
void APatrolPath::RebindWaypointEvents()
{
    UnbindWaypointEvents();

    WaypointBindings.Reset();
    TSet<TWeakObjectPtr<AActor>> BoundActors;

    for (const FPatrolWaypointData& WP : Waypoints)
    {
        AActor* PointActor = WP.Point;
        if (!IsValid(PointActor)) continue;
        if (BoundActors.Contains(PointActor)) continue;
        BoundActors.Add(PointActor);

        FWaypointBinding Binding;
        Binding.Actor = PointActor;

        if (USceneComponent* Root = PointActor->GetRootComponent())
        {
            Binding.TransformHandle = Root->TransformUpdated.AddUObject(
                this, &APatrolPath::HandleWaypointTransformUpdated);
        }

        // OnDestroyed 是动态委托；先移除再添加，避免重复绑定触发 Ensure
        PointActor->OnDestroyed.RemoveDynamic(this, &APatrolPath::HandleWaypointDestroyed);
        PointActor->OnDestroyed.AddDynamic(this, &APatrolPath::HandleWaypointDestroyed);

        WaypointBindings.Add(MoveTemp(Binding));
    }
}

// 解绑路径点修改事件
void APatrolPath::UnbindWaypointEvents()
{
    for (FWaypointBinding& Binding : WaypointBindings)
    {
        AActor* Actor = Binding.Actor.Get();
        if (!Actor) continue;

        if (USceneComponent* Root = Actor->GetRootComponent())
        {
            if (Binding.TransformHandle.IsValid())
            {
                Root->TransformUpdated.Remove(Binding.TransformHandle);
            }
        }

        Actor->OnDestroyed.RemoveDynamic(this, &APatrolPath::HandleWaypointDestroyed);
    }

    WaypointBindings.Reset();
}


void APatrolPath::HandleWaypointTransformUpdated(
    USceneComponent* UpdatedComponent,
    EUpdateTransformFlags UpdateTransformFlags,
    ETeleportType Teleport)
{
    if (bSplineAsPathSource)
    {
        return;
    }
    QueueRebuild();
    BroadcastPathChanged();
}


void APatrolPath::HandleWaypointDestroyed(AActor* DestroyedActor)
{
    if (bSplineAsPathSource)
    {
        return;
    }
    QueueRebuild();
    RebindWaypointEvents(); // 绑定集可能失效，重绑一次
    BroadcastPathChanged();
}


void APatrolPath::QueueRebuild()
{
    if (bRebuildQueued) return;
    bRebuildQueued = true;

    // 合并同帧多次变化，下一帧只重建一次
    GetWorldTimerManager().SetTimerForNextTick(this, &APatrolPath::FlushQueuedRebuild);
}


void APatrolPath::FlushQueuedRebuild()
{
    bRebuildQueued = false;
    RebuildSplineFromWaypoints();
    BroadcastPathChanged();
}

void APatrolPath::EnsureSplineBehaviorCount()
{
    if (!bAutoSyncSplineBehaviorCount || !PatrolSpline)
    {
        return;
    }

    const int32 NumSplinePoints = PatrolSpline->GetNumberOfSplinePoints();
    if (NumSplinePoints <= 0)
    {
        SplinePointBehaviors.Reset();
        return;
    }

    if (SplinePointBehaviors.Num() < NumSplinePoints)
    {
        const int32 ToAdd = NumSplinePoints - SplinePointBehaviors.Num();
        for (int32 i = 0; i < ToAdd; ++i)
        {
            SplinePointBehaviors.Add(FSplinePatrolBehaviorData());
        }
    }
    else if (SplinePointBehaviors.Num() > NumSplinePoints)
    {
        SplinePointBehaviors.SetNum(NumSplinePoints);
    }
}

void APatrolPath::BroadcastPathChanged()
{
    OnPathChanged.Broadcast();
}

void APatrolPath::GetProviderRoutePoints_Implementation(TArray<FVector>& OutPoints) const
{
    GetPatrolRoutePoints(OutPoints);
}

int32 APatrolPath::GetProviderRoutePointCount_Implementation() const
{
    return GetPatrolRoutePointCount();
}

bool APatrolPath::GetProviderRoutePoint_Implementation(int32 Index, FVector& OutPoint) const
{
    return GetPatrolRoutePoint(Index, OutPoint);
}

void APatrolPath::GetProviderBehaviorDataForRoutePoint_Implementation(
    const FVector& RoutePointWorldLocation,
    EWaypointBehavior& OutBehavior,
    float& OutWaitTime,
    float& OutLookAngle,
    float& OutLookSpeed,
    bool& bOutUseCustomLookCenter,
    float& OutLookCenterYawOffset,
    float& OutPreLookPauseTime) const
{
    const FPatrolWaypointData Data = GetBehaviorDataForRoutePoint(RoutePointWorldLocation);
    OutBehavior = Data.Behavior;
    OutWaitTime = Data.WaitTime;
    OutLookAngle = Data.LookAngle;
    OutLookSpeed = Data.LookSpeed;
    bOutUseCustomLookCenter = Data.bUseCustomLookCenter;
    OutLookCenterYawOffset = Data.LookCenterYawOffset;
    OutPreLookPauseTime = Data.PreLookPauseTime;
}

bool APatrolPath::GetProviderBehaviorAnchorYawForRoutePoint_Implementation(const FVector& RoutePointWorldLocation, float& OutYaw) const
{
    return GetBehaviorAnchorYawForRoutePoint(RoutePointWorldLocation, OutYaw);
}

bool APatrolPath::IsProviderClosedLoop_Implementation() const
{
    return bClosedLoop;
}

float APatrolPath::GetProviderRouteLength_Implementation() const
{
    return PatrolSpline ? PatrolSpline->GetSplineLength() : 0.0f;
}

bool APatrolPath::GetProviderRouteTransformAtDistance_Implementation(float DistanceAlongRoute, FVector& OutLocation, FRotator& OutRotation) const
{
    if (!PatrolSpline || PatrolSpline->GetNumberOfSplinePoints() <= 0)
    {
        return false;
    }

    const float SplineLength = PatrolSpline->GetSplineLength();
    if (SplineLength <= KINDA_SMALL_NUMBER)
    {
        OutLocation = PatrolSpline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
        OutRotation = PatrolSpline->GetRotationAtSplinePoint(0, ESplineCoordinateSpace::World);
        return true;
    }

    const float ClampedDistance = FMath::Clamp(DistanceAlongRoute, 0.0f, SplineLength);
    OutLocation = PatrolSpline->GetLocationAtDistanceAlongSpline(ClampedDistance, ESplineCoordinateSpace::World);
    OutRotation = PatrolSpline->GetRotationAtDistanceAlongSpline(ClampedDistance, ESplineCoordinateSpace::World);
    return true;
}

bool APatrolPath::ProjectWorldLocationToRouteDistance_Implementation(const FVector& WorldLocation, float& OutDistanceAlongRoute) const
{
    if (!PatrolSpline || PatrolSpline->GetNumberOfSplinePoints() <= 0)
    {
        return false;
    }

    const float InputKey = PatrolSpline->FindInputKeyClosestToWorldLocation(WorldLocation);
    OutDistanceAlongRoute = PatrolSpline->GetDistanceAlongSplineAtSplineInputKey(InputKey);
    return true;
}

bool APatrolPath::GetNearestSplineControlPointIndex_Implementation(const FVector& WorldLocation, int32& OutIndex, float& OutDistSq) const
{
    OutIndex = INDEX_NONE;
    OutDistSq = TNumericLimits<float>::Max();

    if (!PatrolSpline || PatrolSpline->GetNumberOfSplinePoints() <= 0)
    {
        return false;
    }

    float BestDistSq = TNumericLimits<float>::Max();
    int32 BestIndex = INDEX_NONE;
    const int32 Num = PatrolSpline->GetNumberOfSplinePoints();
    for (int32 i = 0; i < Num; ++i)
    {
        const FVector Loc = PatrolSpline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
        const float Dsq = FVector::DistSquared(WorldLocation, Loc);
        if (Dsq < BestDistSq)
        {
            BestDistSq = Dsq;
            BestIndex = i;
        }
    }

    OutIndex = BestIndex;
    OutDistSq = BestDistSq;
    return BestIndex != INDEX_NONE;
}