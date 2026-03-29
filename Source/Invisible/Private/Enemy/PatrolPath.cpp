// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/PatrolPath.h"
#include "DrawDebugHelpers.h"

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
	
    // 绑定路径点修改事件
    RebindWaypointEvents();
    // 重建样条线
    RebuildSplineFromWaypoints();
}

void APatrolPath::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // 解绑路径点修改事件
    UnbindWaypointEvents();

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

// 通过 Spline 绘制巡逻路径
void APatrolPath::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    
    // 绑定路径点修改事件
    RebindWaypointEvents();
    // 重建样条线
    RebuildSplineFromWaypoints();
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
        PatrolSpline->SetSplinePointType(i, ESplinePointType::Linear, false);
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

    const FName Changed = PropertyChangedEvent.GetPropertyName();
    if (Changed == WaypointsName || Changed == ClosedLoopName)
    {
        RebindWaypointEvents();
        QueueRebuild();
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
    QueueRebuild();
}


void APatrolPath::HandleWaypointDestroyed(AActor* DestroyedActor)
{
    QueueRebuild();
    RebindWaypointEvents(); // 绑定集可能失效，重绑一次
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
}