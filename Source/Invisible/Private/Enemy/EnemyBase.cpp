// Fill out your copyright notice in the Description page of Project Settings.
#include "Enemy/EnemyBase.h"
#include "Enemy/EnemyAIController.h"
#include "Enemy/PatrolPath.h"
#include "Enemy/PatrolRouteProvider.h"
#include "Enemy/Trait/TraitDefinition.h"
#include "Enemy/Trait/TraitSubsystem.h"
#include "Engine/GameInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Components/WidgetComponent.h>
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Enemy/UI/AIInteractionButtonsWidget.h"
#include "Enemy/UI/AIDialogueBubbleWidget.h"
#include "MotionWarpingComponent.h"
#include "Components/ActorComponent.h"
#include "Actors/Waypoint.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAIEnemyInteractionDebug, Log, All);
// DEFINE_LOG_CATEGORY_STATIC(LogAIPatrolRoute, Log, All);


// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// 绑定 AI Controller
	AIControllerClass = AEnemyAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 设置角色的转身速度
	bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->bUseControllerDesiredRotation = false;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);

	AlertBarWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("AlertBarWidgetComp"));
	AlertBarWidgetComp->SetupAttachment(GetMesh());
	AlertBarWidgetComp->SetWidgetSpace(EWidgetSpace::Screen); // 屏幕空间
	AlertBarWidgetComp->SetDrawSize(FVector2D(120.f, 16.f));
	AlertBarWidgetComp->SetRelativeLocation(FVector(0.f, 0.f, 220.f));

	AlertBarWidgetComp->SetDrawAtDesiredSize(true);      // 跟随Widget实际尺寸
	AlertBarWidgetComp->SetPivot(FVector2D(0.5f, 1.0f)); // 底边中心对齐到头顶点
	AlertBarWidgetComp->SetVisibility(false);             // 默认隐藏，警戒>0再显示

    // 按键组件
    InteractionButtonsWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionButtonsWidgetComp"));
    InteractionButtonsWidgetComp->SetupAttachment(GetCapsuleComponent());
    InteractionButtonsWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
    InteractionButtonsWidgetComp->SetDrawAtDesiredSize(false);
    InteractionButtonsWidgetComp->SetDrawSize(FVector2D(500.f, 120.f));
    InteractionButtonsWidgetComp->SetPivot(FVector2D(0.5f, 0.0f));
    InteractionButtonsWidgetComp->SetRelativeRotation(FRotator::ZeroRotator);
    InteractionButtonsWidgetComp->SetRelativeScale3D(FVector::OneVector);
    InteractionButtonsWidgetComp->SetRelativeLocation(FVector(0.f, 0.f, 140.f));
    InteractionButtonsWidgetComp->SetVisibility(false);

    // 对话框组件
    DialogueBubbleWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("DialogueBubbleWidgetComp"));
    DialogueBubbleWidgetComp->SetupAttachment(GetCapsuleComponent());
    DialogueBubbleWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
    DialogueBubbleWidgetComp->SetDrawAtDesiredSize(true);
    DialogueBubbleWidgetComp->SetPivot(FVector2D(0.5f, 1.0f));
    DialogueBubbleWidgetComp->SetRelativeRotation(FRotator::ZeroRotator);
    DialogueBubbleWidgetComp->SetRelativeScale3D(FVector::OneVector);
    DialogueBubbleWidgetComp->SetRelativeLocation(FVector(0.f, 0.f, 185.f)); // 比交互按钮略高
    DialogueBubbleWidgetComp->SetVisibility(false);

    // 运动扭曲组件
    MotionWarpingComp = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComp"));
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

    RegisterIgnoreCollisionWithOtherEnemies();

    // 初始化头顶按键
    if(InteractionButtonsWidgetClass && InteractionButtonsWidgetComp)
    {
        InteractionButtonsWidgetComp->SetWidgetClass(InteractionButtonsWidgetClass);
        InteractionButtonsWidgetComp->InitWidget();
    }
	
    // 初始化头顶对话框
    if(DialogueBubbleWidgetClass && DialogueBubbleWidgetComp)
    {
        DialogueBubbleWidgetComp->SetWidgetClass(DialogueBubbleWidgetClass);
        DialogueBubbleWidgetComp->InitWidget();
        DialogueBubbleWidgetComp->SetVisibility(false, true);
    }
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (bDebugDrawWaypointChain && IsValid(NextWaypoint) && IsValid(NextWaypoint->NextWaypoint))
    {
        const FVector Start = NextWaypoint->GetActorLocation() + FVector(0.f, 0.f, 20.f);
        const FVector End = NextWaypoint->NextWaypoint->GetActorLocation() + FVector(0.f, 0.f, 20.f);
        DrawDebugLine(GetWorld(), Start, End, FColor::Cyan, false, 0.f, 0, 2.f);
    }
}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// 获取下一个巡逻点
AActor* AEnemyBase::GetNextPatrolPoint()
{
    if (IsValid(NextWaypoint))
    {
        return NextWaypoint;
    }

	if (!AssignedPatrolPath) return nullptr;

    const int32 Count = AssignedPatrolPath->Num();
    if (Count <= 0)
    {
        return nullptr;
    }

    const int32 SafeIndex = ((CurrentPatrolPointIndex % Count) + Count) % Count;
	return AssignedPatrolPath->GetWaypoint(SafeIndex);
}

void AEnemyBase::AdvanceToNextWaypoint()
{
    if (IsValid(NextWaypoint))
    {
        NextWaypoint = NextWaypoint->NextWaypoint;
    }
}

void AEnemyBase::ClearAndDestroyWaypointChain()
{
    if (!IsValid(NextWaypoint))
    {
        return;
    }

    TSet<AWaypoint*> Visited;
    AWaypoint* Cursor = NextWaypoint;
    while (IsValid(Cursor) && !Visited.Contains(Cursor))
    {
        Visited.Add(Cursor);
        AWaypoint* Next = Cursor->NextWaypoint;
        Cursor->NextWaypoint = nullptr;
        Cursor->Destroy();
        Cursor = Next;
    }

    NextWaypoint = nullptr;
}

bool AEnemyBase::GetCurrentPatrolLocation(FVector& OutLocation) const
{
    UObject* ProviderObject = ResolvePatrolRouteProviderObject();
    if (!ProviderObject)
    {
        // UE_LOG(LogAIPatrolRoute, Warning, TEXT("[%s] Patrol provider not resolved."), *GetNameSafe(this));
        // UE_LOG(LogTemp, Warning, TEXT("[PatrolRoute] %s provider unresolved. PatrolRouteProviderActor=%s AssignedPatrolPath=%s"),
        //     *GetNameSafe(this), *GetNameSafe(PatrolRouteProviderActor), *GetNameSafe(AssignedPatrolPath));
        return false;
    }

    const int32 RoutePointCount = IPatrolRouteProvider::Execute_GetProviderRoutePointCount(ProviderObject);
    if (RoutePointCount <= 0)
    {
        // UE_LOG(LogAIPatrolRoute, Warning, TEXT("[%s] RoutePointCount <= 0. Provider=%s"), *GetNameSafe(this), *GetNameSafe(Cast<UObject>(ProviderObject)));
        // UE_LOG(LogTemp, Warning, TEXT("[PatrolRoute] %s provider=%s RoutePointCount=%d"),
        //     *GetNameSafe(this), *GetNameSafe(Cast<UObject>(ProviderObject)), RoutePointCount);
        return false;
    }

    const int32 SafeIndex = ((CurrentPatrolPointIndex % RoutePointCount) + RoutePointCount) % RoutePointCount;
    return IPatrolRouteProvider::Execute_GetProviderRoutePoint(ProviderObject, SafeIndex, OutLocation);
}

int32 AEnemyBase::GetPatrolRoutePointCount() const
{
    UObject* ProviderObject = ResolvePatrolRouteProviderObject();
    if (!ProviderObject)
    {
        // UE_LOG(LogAIPatrolRoute, Warning, TEXT("[%s] GetPatrolRoutePointCount failed: provider not resolved."), *GetNameSafe(this));
        // UE_LOG(LogTemp, Warning, TEXT("[PatrolRoute] %s GetPatrolRoutePointCount failed: provider unresolved."), *GetNameSafe(this));
        return 0;
    }

    const int32 Count = IPatrolRouteProvider::Execute_GetProviderRoutePointCount(ProviderObject);
    // UE_LOG(LogTemp, Warning, TEXT("[PatrolRoute] %s provider=%s count=%d"), *GetNameSafe(this), *GetNameSafe(Cast<UObject>(ProviderObject)), Count);
    return Count;
}

void AEnemyBase::GetAllPatrolRoutePoints(TArray<FVector>& OutPoints) const
{
    OutPoints.Reset();
    UObject* ProviderObject = ResolvePatrolRouteProviderObject();
    if (ProviderObject)
    {
        IPatrolRouteProvider::Execute_GetProviderRoutePoints(ProviderObject, OutPoints);
    }
}

bool AEnemyBase::GetPatrolRouteLength(float& OutLength) const
{
    OutLength = 0.0f;

    UObject* ProviderObject = ResolvePatrolRouteProviderObject();
    if (!ProviderObject)
    {
        return false;
    }

    OutLength = IPatrolRouteProvider::Execute_GetProviderRouteLength(ProviderObject);
    return OutLength > KINDA_SMALL_NUMBER;
}

bool AEnemyBase::GetPatrolRouteTransformAtDistance(float DistanceAlongRoute, FVector& OutLocation, FRotator& OutRotation) const
{
    UObject* ProviderObject = ResolvePatrolRouteProviderObject();
    if (!ProviderObject)
    {
        return false;
    }

    return IPatrolRouteProvider::Execute_GetProviderRouteTransformAtDistance(
        ProviderObject,
        DistanceAlongRoute,
        OutLocation,
        OutRotation);
}

bool AEnemyBase::ProjectWorldLocationToPatrolDistance(const FVector& WorldLocation, float& OutDistanceAlongRoute) const
{
    UObject* ProviderObject = ResolvePatrolRouteProviderObject();
    if (!ProviderObject)
    {
        return false;
    }

    return IPatrolRouteProvider::Execute_ProjectWorldLocationToRouteDistance(
        ProviderObject,
        WorldLocation,
        OutDistanceAlongRoute);
}

bool AEnemyBase::IsPatrolRouteClosedLoop() const
{
    UObject* ProviderObject = ResolvePatrolRouteProviderObject();
    if (!ProviderObject)
    {
        return false;
    }

    return IPatrolRouteProvider::Execute_IsProviderClosedLoop(ProviderObject);
}

FPatrolWaypointData AEnemyBase::GetCurrentPatrolBehaviorData(const FVector& ArrivedLocation) const
{
    FPatrolWaypointData Data;
    Data.Behavior = EWaypointBehavior::None;
    Data.WaitTime = 0.0f;

    UObject* ProviderObject = ResolvePatrolRouteProviderObject();
    if (!ProviderObject)
    {
        return Data;
    }

    EWaypointBehavior OutBehavior = EWaypointBehavior::None;
    float OutWaitTime = 0.0f;
    float OutLookAngle = 0.0f;
    float OutLookSpeed = 0.0f;
    bool bOutUseCustomLookCenter = false;
    float OutLookCenterYawOffset = 0.0f;
    float OutPreLookPauseTime = 0.0f;
    IPatrolRouteProvider::Execute_GetProviderBehaviorDataForRoutePoint(
        ProviderObject,
        ArrivedLocation,
        OutBehavior,
        OutWaitTime,
        OutLookAngle,
        OutLookSpeed,
        bOutUseCustomLookCenter,
        OutLookCenterYawOffset,
        OutPreLookPauseTime);

    Data.Behavior = OutBehavior;
    Data.WaitTime = OutWaitTime;
    Data.LookAngle = OutLookAngle;
    Data.LookSpeed = OutLookSpeed;
    Data.bUseCustomLookCenter = bOutUseCustomLookCenter;
    Data.LookCenterYawOffset = OutLookCenterYawOffset;
    Data.PreLookPauseTime = OutPreLookPauseTime;
    Data.Point = nullptr;
    return Data;
}

bool AEnemyBase::GetCurrentPatrolBehaviorAnchorYaw(const FVector& ArrivedLocation, float& OutYaw) const
{
    UObject* ProviderObject = ResolvePatrolRouteProviderObject();
    if (!ProviderObject)
    {
        return false;
    }

    return IPatrolRouteProvider::Execute_GetProviderBehaviorAnchorYawForRoutePoint(ProviderObject, ArrivedLocation, OutYaw);
}

void AEnemyBase::RegisterIgnoreCollisionWithOtherEnemies()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    UCapsuleComponent* MyCapsule = GetCapsuleComponent();
    if (!MyCapsule)
    {
        return;
    }

    for (TActorIterator<AEnemyBase> It(World); It; ++It)
    {
        AEnemyBase* Other = *It;
        if (!Other || Other == this)
        {
            continue;
        }

        UCapsuleComponent* OtherCapsule = Other->GetCapsuleComponent();
        if (!OtherCapsule)
        {
            continue;
        }

        MyCapsule->IgnoreActorWhenMoving(Other, true);
        OtherCapsule->IgnoreActorWhenMoving(this, true);
    }
}

void AEnemyBase::UpdatePatrolBehaviorAnchorCooldown(const FVector& ActorWorldLocation)
{
    const FPatrolWaypointData Data = GetCurrentPatrolBehaviorData(ActorWorldLocation);
    if (Data.Behavior == EWaypointBehavior::None)
    {
        PatrolBehaviorCooldownSplinePointIndex = INDEX_NONE;
    }
}

bool AEnemyBase::TryGetNearestPatrolSplinePointIndex(const FVector& WorldLocation, int32& OutIndex, float& OutDistSq) const
{
    OutIndex = INDEX_NONE;
    OutDistSq = 0.0f;

    UObject* ProviderObject = ResolvePatrolRouteProviderObject();
    if (!ProviderObject)
    {
        return false;
    }

    return IPatrolRouteProvider::Execute_GetNearestSplineControlPointIndex(
        ProviderObject,
        WorldLocation,
        OutIndex,
        OutDistSq);
}

UObject* AEnemyBase::ResolvePatrolRouteProviderObject() const
{
    if (IsValid(PatrolRouteProviderActor))
    {
        TInlineComponentArray<UActorComponent*> Components(PatrolRouteProviderActor);
        for (UActorComponent* Comp : Components)
        {
            if (IsValid(Comp) && Comp->GetClass()->ImplementsInterface(UPatrolRouteProvider::StaticClass()))
            {
                // UE_LOG(LogAIPatrolRoute, Verbose, TEXT("[%s] Using provider component interface: %s on %s"), *GetNameSafe(this), *GetNameSafe(Comp), *GetNameSafe(PatrolRouteProviderActor));
                // UE_LOG(LogTemp, Warning, TEXT("[PatrolRoute] %s resolved provider component: %s"), *GetNameSafe(this), *GetNameSafe(Comp));
                return Comp;
            }
        }

        if (PatrolRouteProviderActor->GetClass()->ImplementsInterface(UPatrolRouteProvider::StaticClass()))
        {
            // UE_LOG(LogAIPatrolRoute, Verbose, TEXT("[%s] Using provider actor interface: %s"), *GetNameSafe(this), *GetNameSafe(PatrolRouteProviderActor));
            // UE_LOG(LogTemp, Warning, TEXT("[PatrolRoute] %s resolved provider actor interface: %s"), *GetNameSafe(this), *GetNameSafe(PatrolRouteProviderActor));
            return PatrolRouteProviderActor;
        }

        // UE_LOG(LogAIPatrolRoute, Warning, TEXT("[%s] PatrolRouteProviderActor set (%s) but no interface found on actor or components."),
        //     *GetNameSafe(this), *GetNameSafe(PatrolRouteProviderActor));
        // UE_LOG(LogTemp, Warning, TEXT("[PatrolRoute] %s provider actor has no interface/component: %s"),
        //     *GetNameSafe(this), *GetNameSafe(PatrolRouteProviderActor));
    }

    if (IsValid(AssignedPatrolPath) && AssignedPatrolPath->GetClass()->ImplementsInterface(UPatrolRouteProvider::StaticClass()))
    {
        // UE_LOG(LogAIPatrolRoute, Verbose, TEXT("[%s] Fallback to AssignedPatrolPath provider: %s"), *GetNameSafe(this), *GetNameSafe(AssignedPatrolPath));
        return AssignedPatrolPath;
    }

    // UE_LOG(LogAIPatrolRoute, Warning, TEXT("[%s] No patrol provider. PatrolRouteProviderActor=%s AssignedPatrolPath=%s"),
    //     *GetNameSafe(this), *GetNameSafe(PatrolRouteProviderActor), *GetNameSafe(AssignedPatrolPath));
    return nullptr;
}

// 设置状态标签 
void AEnemyBase::SetAIStateTag(FGameplayTag NewTag)
{
    if (!NewTag.IsValid()) return;
    if (AIStateTags.HasTagExact(NewTag)) return;

    AIStateTags.Reset();
    AIStateTags.AddTag(NewTag);

    UE_LOG(LogTemp, Log, TEXT("[AI] StateTag -> %s"), *AIStateTags.ToStringSimple());
}

void AEnemyBase::GetTraitDisplayEntries(UObject* WorldContextObject, TArray<FTraitDisplayEntry>& OutEntries) const
{
    OutEntries.Reset();

    const UWorld* World = WorldContextObject ? WorldContextObject->GetWorld() : GetWorld();
    if (!World)
    {
        return;
    }

    UGameInstance* GI = World->GetGameInstance();
    UTraitSubsystem* TraitSub = GI ? GI->GetSubsystem<UTraitSubsystem>() : nullptr;
    if (!TraitSub)
    {
        return;
    }

    TArray<UTraitDefinition*> TraitDefs;
    TraitSub->ResolveTraitDefs(TraitTags, TraitDefs);

    for (const UTraitDefinition* Def : TraitDefs)
    {
        if (!Def)
        {
            continue;
        }

        bool bHasAIWithAI = false;
        bool bHasAIWithObject = false;

        for (const FTraitInteractionRule& Rule : Def->Rules)
        {
            if (Rule.InteractionType == ETraitInteractionType::AI_With_AI)
            {
                bHasAIWithAI = true;
            }
            else if (Rule.InteractionType == ETraitInteractionType::AI_With_Object)
            {
                bHasAIWithObject = true;
            }
        }

        ETraitDisplayCategory Category = ETraitDisplayCategory::Unknown;
        if (bHasAIWithAI)
        {
            Category = ETraitDisplayCategory::AIWithAI;
        }
        else if (bHasAIWithObject)
        {
            Category = ETraitDisplayCategory::AIWithObject;
        }

        FTraitDisplayEntry Entry;
        Entry.TraitTag = Def->TraitTag;
        Entry.DisplayName = Def->DisplayName.IsEmpty() ? FText::FromName(Def->TraitTag.GetTagName()) : Def->DisplayName;
        Entry.Category = Category;
        OutEntries.Add(MoveTemp(Entry));
    }
}

FText AEnemyBase::BuildTraitDisplayText(UObject* WorldContextObject, bool bUseRichTextMarkup) const
{
    TArray<FTraitDisplayEntry> Entries;
    GetTraitDisplayEntries(WorldContextObject, Entries);

    if (Entries.IsEmpty())
    {
        return FText::GetEmpty();
    }

    const FString Separator = TraitPanelFormatSettings.Separator.IsEmpty() ? TEXT(" | ") : TraitPanelFormatSettings.Separator;
    FString Result;
    Result.Reserve(Entries.Num() * 12);

    auto AppendWithStyle = [&](const FName& StyleTag, const FString& RawText)
    {
        if (bUseRichTextMarkup && !StyleTag.IsNone())
        {
            Result += FString::Printf(TEXT("<%s>%s</>"), *StyleTag.ToString(), *RawText);
        }
        else
        {
            Result += RawText;
        }
    };

    for (int32 Index = 0; Index < Entries.Num(); ++Index)
    {
        if (Index > 0)
        {
            Result += Separator;
        }

        const FString NameString = Entries[Index].DisplayName.ToString();
        switch (Entries[Index].Category)
        {
        case ETraitDisplayCategory::AIWithAI:
            AppendWithStyle(TraitPanelFormatSettings.AIWithAIStyleTag, NameString);
            break;
        case ETraitDisplayCategory::AIWithObject:
            AppendWithStyle(TraitPanelFormatSettings.AIWithObjectStyleTag, NameString);
            break;
        default:
            AppendWithStyle(TraitPanelFormatSettings.UnknownStyleTag, NameString);
            break;
        }
    }

    return FText::FromString(Result);
}

FAIInfoData AEnemyBase::BuildAIInfoDataForPanel(UObject* WorldContextObject, bool bUseRichTextMarkup) const
{
    FAIInfoData OutData = AIInfoData;
    OutData.EnemyTrait = BuildTraitDisplayText(WorldContextObject, bUseRichTextMarkup);
    return OutData;
}


// ===== ai交互UI相关 =====

// 显示头顶交互按钮
void AEnemyBase::ShowInteractionButtons(const TArray<FInteractionActionOption>& InActions, AEnemyBase* InSourceAI)
{
    if(!InteractionButtonsWidgetComp) return;
    
    if (InteractionButtonsWidgetClass && !InteractionButtonsWidgetComp->GetWidgetClass())
    {
        InteractionButtonsWidgetComp->SetWidgetClass(InteractionButtonsWidgetClass);
        InteractionButtonsWidgetComp->InitWidget();
    }

    UAIInteractionButtonsWidget* Widget = Cast<UAIInteractionButtonsWidget>(InteractionButtonsWidgetComp->GetUserWidgetObject());
    if (!Widget) 
    {
        UE_LOG(LogTemp, Warning, TEXT("显示头顶交互按钮失败: %s"), *GetNameSafe(InSourceAI));
        return;
    }

    // 绑定按键点击事件
    if (!Widget->OnActionClicked.IsAlreadyBound(this, &AEnemyBase::HandleInteractionButtonClicked))
    {
        Widget->OnActionClicked.AddDynamic(this, &AEnemyBase::HandleInteractionButtonClicked);
    }

    Widget->SetupAction(InActions, InSourceAI, this);
    InteractionButtonsWidgetComp->SetVisibility(InActions.Num() > 0,true);

    UE_LOG(LogTemp, Log, TEXT("显示头顶交互按钮: %s"), *GetNameSafe(InSourceAI));
    UE_LOG(LogAIEnemyInteractionDebug, Log, TEXT("[显示头顶交互按钮] Enter Self=%s Source=%s InActions=%d Comp=%s WidgetClass=%s"),
    *GetNameSafe(this),
    *GetNameSafe(InSourceAI),
    InActions.Num(),
    *GetNameSafe(InteractionButtonsWidgetComp),
    *GetNameSafe(InteractionButtonsWidgetClass));
}

// 隐藏头顶交互按钮
void AEnemyBase::HideInteractionButtons()
{
    if(!InteractionButtonsWidgetComp) return;

    if(UAIInteractionButtonsWidget* Widget = Cast<UAIInteractionButtonsWidget>(InteractionButtonsWidgetComp->GetUserWidgetObject()))
    {
        Widget->ClearActions();
    }

    InteractionButtonsWidgetComp->SetVisibility(false,true);
}

// 按键点击句柄
void AEnemyBase::HandleInteractionButtonClicked(
    FInteractionActionOption ActionData,
    AEnemyBase* SourceAI,
    AActor* TargetActor)
{
    OnInteractionActionChosen.Broadcast(ActionData, SourceAI, TargetActor);
}


// ===== ai对话框相关 =====

// 显示头顶对话框
void AEnemyBase::ShowDialogueBubble(const FText& InText)
{
    if(!DialogueBubbleWidgetComp) return;

    if(InText.IsEmpty())
    {
        HideDialogueBubble();
        return;
    }

    if(DialogueBubbleWidgetClass && !DialogueBubbleWidgetComp->GetWidgetClass())
    {
        DialogueBubbleWidgetComp->SetWidgetClass(DialogueBubbleWidgetClass);
        DialogueBubbleWidgetComp->InitWidget();
    }

    UAIDialogueBubbleWidget* Widget = Cast<UAIDialogueBubbleWidget>(DialogueBubbleWidgetComp->GetUserWidgetObject());
    if(!Widget)
    {
        UE_LOG(LogTemp, Warning, TEXT("显示头顶对话框失败: %s"), *GetNameSafe(this));
        return;
    }

    Widget->ShowDialogueText(InText);
    DialogueBubbleWidgetComp->SetVisibility(true, true);
}

// 隐藏头顶对话框
void AEnemyBase::HideDialogueBubble()
{
    if(!DialogueBubbleWidgetComp) return;

    if(UAIDialogueBubbleWidget* Widget = Cast<UAIDialogueBubbleWidget>(DialogueBubbleWidgetComp->GetUserWidgetObject()))
    {
        Widget->ClearDialogueText();
    }

    DialogueBubbleWidgetComp->SetVisibility(false, true);
}
