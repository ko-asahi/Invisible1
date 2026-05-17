#include "Enemy/SecurityCameraEnemy.h"

#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Invisible_GameModeBase.h"
#include "InvisiblePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Data/SIZZ_IndicatorBehaviourDefinition.h"
#include "Data/SIZZ_CustomIndicatorRefreshValue.h"
#include "Decals/SIZZ_DecalBaseActor.h"
#include "SpellIndicatorLibrary/SIZZ_SpellIndicatorLibrary.h"

namespace
{
bool IsSafeSightIndicatorDefinition(const USIZZ_IndicatorBehaviourDefinition* IndicatorDefinition)
{
    return IndicatorDefinition
        && IndicatorDefinition->IndicatorClassToSpawn
        && IndicatorDefinition->IndicatorMaterial
        && IndicatorDefinition->IndicatorAnimationCurve
        && IndicatorDefinition->RefreshData
        && IndicatorDefinition->RefreshData->RefreshValue > 0.0f;
}

ASIZZ_DecalBaseActor* SpawnSightIndicatorConeByReflection(
    UObject* WorldObjContext,
    USIZZ_IndicatorBehaviourDefinition* IndicatorDefinition,
    const FVector& Position,
    const FRotator& Rotation,
    float Time,
    float Height,
    float Width)
{
    UClass* LibraryClass = USIZZ_SpellIndicatorLibrary::StaticClass();
    if (!LibraryClass)
    {
        return nullptr;
    }

    UFunction* SpawnFunc = LibraryClass->FindFunctionByName(TEXT("SpawnIndicatorCone"));
    if (!SpawnFunc)
    {
        return nullptr;
    }

    struct FSpawnIndicatorConeParams
    {
        UObject* WorldObjContext = nullptr;
        USIZZ_IndicatorBehaviourDefinition* IndicatorDefinition = nullptr;
        FVector Position = FVector::ZeroVector;
        FRotator Rotation = FRotator::ZeroRotator;
        float Time = 1.0f;
        float Height = 100.0f;
        float Width = 100.0f;
        bool bOffsetByWidth = true;
        bool bFlipCone = false;
        ASIZZ_DecalBaseActor* ReturnValue = nullptr;
    };

    FSpawnIndicatorConeParams Params;
    Params.WorldObjContext = WorldObjContext;
    Params.IndicatorDefinition = IndicatorDefinition;
    Params.Position = Position;
    Params.Rotation = Rotation;
    Params.Time = Time;
    Params.Height = Height;
    Params.Width = Width;
    Params.bOffsetByWidth = true;
    Params.bFlipCone = false;

    UObject* LibraryCDO = LibraryClass->GetDefaultObject();
    if (!LibraryCDO)
    {
        return nullptr;
    }

    LibraryCDO->ProcessEvent(SpawnFunc, &Params);
    return Params.ReturnValue;
}

void SetSightIndicatorHiddenState(ASIZZ_DecalBaseActor* Indicator, bool bHidden)
{
    if (IsValid(Indicator))
    {
        Indicator->SetActorHiddenInGame(bHidden);
        Indicator->SetActorEnableCollision(false);
        Indicator->SetActorTickEnabled(false);
    }
}
}

ASecurityCameraEnemy::ASecurityCameraEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    CameraMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraMesh"));
    CameraMesh->SetupAttachment(RootComponent);
    CameraMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    AlertBarWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("AlertBarWidgetComp"));
    AlertBarWidgetComp->SetupAttachment(RootComponent);
    AlertBarWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
    AlertBarWidgetComp->SetDrawSize(FVector2D(120.0f, 16.0f));
    AlertBarWidgetComp->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
    AlertBarWidgetComp->SetDrawAtDesiredSize(true);
    AlertBarWidgetComp->SetPivot(FVector2D(0.5f, 1.0f));
    AlertBarWidgetComp->SetVisibility(false);
}

void ASecurityCameraEnemy::BeginPlay()
{
    Super::BeginPlay();

    DetectionInterval = FMath::Clamp(DetectionInterval, 0.02f, 1.0f);
    UpdateAlertWidgetVisibility();
    CreateSightIndicator();
    EvaluateDetection();

    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(
            DetectionTimerHandle,
            this,
            &ASecurityCameraEnemy::EvaluateDetection,
            DetectionInterval,
            true);
    }
}

void ASecurityCameraEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(DetectionTimerHandle);
    }

    DestroySightIndicator();

    Super::EndPlay(EndPlayReason);
}

void ASecurityCameraEnemy::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    UpdateSightIndicatorTransform();
}

float ASecurityCameraEnemy::GetAlertnessNormalized_Implementation() const
{
    return MaxAlertness > 0.0f ? Alertness / MaxAlertness : 0.0f;
}

void ASecurityCameraEnemy::SetCameraDisabled(bool bDisabled)
{
    if (bCameraDisabled == bDisabled)
    {
        return;
    }

    bCameraDisabled = bDisabled;
    bPlayerInSight = false;

    if (bCameraDisabled)
    {
        Alertness = 0.0f;
    }

    UpdateSightIndicatorVisibility();
    UpdateAlertWidgetVisibility();
}

void ASecurityCameraEnemy::EvaluateDetection()
{
    if (bCameraDisabled)
    {
        bPlayerInSight = false;
        Alertness = 0.0f;
        UpdateSightIndicatorVisibility();
        UpdateAlertWidgetVisibility();
        return;
    }

    if (bGameOverTriggered)
    {
        return;
    }

    if (const AInvisible_GameModeBase* GameMode = Cast<AInvisible_GameModeBase>(UGameplayStatics::GetGameMode(this)))
    {
        if (GameMode->IsGameOverStarted())
        {
            bGameOverTriggered = true;
            return;
        }
    }

    if (const AInvisiblePlayerController* PlayerController = Cast<AInvisiblePlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
    {
        if (PlayerController->bIsEditMode)
        {
            bPlayerInSight = false;
            UpdateSightIndicatorVisibility();
            return;
        }
    }

    float Distance = 0.0f;
    const bool bInSight = IsPlayerInSightInternal(Distance);
    bPlayerInSight = bInSight;
    UpdateSightIndicatorVisibility();

    const float Dt = FMath::Max(DetectionInterval, KINDA_SMALL_NUMBER);
    if (bInSight)
    {
        Alertness += AlertGainRate * Dt;
    }
    else if (bDecayWhenPlayerLost)
    {
        Alertness -= AlertDecayRate * Dt;
    }

    Alertness = FMath::Clamp(Alertness, 0.0f, MaxAlertness);

    const float AlertProgress = MaxAlertness > KINDA_SMALL_NUMBER ? Alertness / MaxAlertness : 0.0f;
    if (IsValid(SightIndicatorActor))
    {
        SightIndicatorActor->SetIndicatorProgress(AlertProgress);
    }

    UpdateAlertWidgetVisibility();

    if (Alertness >= MaxAlertness - KINDA_SMALL_NUMBER)
    {
        TriggerGameOver();
    }
}

bool ASecurityCameraEnemy::IsPlayerInSightInternal(float& OutDistance) const
{
    OutDistance = 0.0f;

    UWorld* World = GetWorld();
    if (!World)
    {
        return false;
    }

    ACharacter* Player = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(World, 0));
    if (!Player)
    {
        return false;
    }

    const FVector EyeLocation = CameraMesh ? CameraMesh->GetComponentLocation() : GetActorLocation();
    const FVector PlayerLocation = Player->GetActorLocation();

    const FVector2D Eye2D(EyeLocation.X, EyeLocation.Y);
    const FVector2D Player2D(PlayerLocation.X, PlayerLocation.Y);
    const FVector2D ToPlayer2D = Player2D - Eye2D;

    const float Distance2D = ToPlayer2D.Size();
    OutDistance = Distance2D;
    if (Distance2D > SightRadius)
    {
        return false;
    }

    FVector2D Forward2D(GetActorForwardVector().X, GetActorForwardVector().Y);
    Forward2D = Forward2D.GetSafeNormal();
    if (Forward2D.IsNearlyZero())
    {
        return false;
    }

    const FVector2D ToPlayerDir = ToPlayer2D.GetSafeNormal();
    if (ToPlayerDir.IsNearlyZero())
    {
        return true;
    }

    const float Dot = FVector2D::DotProduct(Forward2D, ToPlayerDir);
    const float CosHalfAngle = FMath::Cos(FMath::DegreesToRadians(HalfViewAngle));
    if (Dot < CosHalfAngle)
    {
        return false;
    }

    FHitResult HitResult;
    FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(SecurityCameraSightTrace), false, this);
    QueryParams.AddIgnoredActor(this);
    const bool bHit = World->LineTraceSingleByChannel(HitResult, EyeLocation, PlayerLocation, ECC_Visibility, QueryParams);
    if (bHit && HitResult.GetActor() != Player)
    {
        return false;
    }

    if (bDrawDebugSight)
    {
        const FVector Forward = GetActorForwardVector();
        const FVector LeftDir = Forward.RotateAngleAxis(HalfViewAngle, FVector::UpVector);
        const FVector RightDir = Forward.RotateAngleAxis(-HalfViewAngle, FVector::UpVector);
        DrawDebugLine(World, EyeLocation, EyeLocation + LeftDir * SightRadius, FColor::Green, false, DetectionInterval * 1.1f, 0, 2.0f);
        DrawDebugLine(World, EyeLocation, EyeLocation + RightDir * SightRadius, FColor::Green, false, DetectionInterval * 1.1f, 0, 2.0f);
        DrawDebugLine(World, EyeLocation, PlayerLocation, FColor::Yellow, false, DetectionInterval * 1.1f, 0, 1.0f);
    }

    return true;
}

void ASecurityCameraEnemy::TriggerGameOver()
{
    if (bGameOverTriggered)
    {
        return;
    }

    AInvisible_GameModeBase* GameMode = Cast<AInvisible_GameModeBase>(UGameplayStatics::GetGameMode(this));
    if (!GameMode || GameMode->IsGameOverStarted())
    {
        bGameOverTriggered = true;
        return;
    }

    GameMode->BeginGameOverWithDelay(nullptr, CameraGameOverDelay);
    bGameOverTriggered = true;
}

void ASecurityCameraEnemy::UpdateAlertWidgetVisibility() const
{
    if (!AlertBarWidgetComp)
    {
        return;
    }

    AlertBarWidgetComp->SetVisibility(Alertness > KINDA_SMALL_NUMBER);
}

bool ASecurityCameraEnemy::ShouldShowSightIndicator() const
{
    if (!bEnableSightIndicator)
    {
        return false;
    }

    if (bOnlyShowSightIndicatorInEditor)
    {
#if WITH_EDITOR
        return true;
#else
        return false;
#endif
    }

    return true;
}

void ASecurityCameraEnemy::CreateSightIndicator()
{
    DestroySightIndicator();

    if (!ShouldShowSightIndicator() || !IsSafeSightIndicatorDefinition(SightIndicatorDefinition))
    {
        return;
    }

    const FVector SightLocation = (CameraMesh ? CameraMesh->GetComponentLocation() : GetActorLocation()) + FVector(0.0f, 0.0f, SightIndicatorZOffset);
    const FRotator SightRotation = GetActorRotation() + FRotator(0.0f, -90.0f, 0.0f);
    const float SafeHeight = FMath::Max(SightRadius, 1.0f);
    const float VisualHalfAngle = FMath::Clamp(HalfViewAngle * FMath::Max(SightIndicatorHalfAngleScale, 0.1f), 1.0f, 89.0f);
    const float SafeWidth = FMath::Max(SafeHeight * FMath::Tan(FMath::DegreesToRadians(VisualHalfAngle)), 1.0f);
    const float Lifetime = FMath::Max(SightIndicatorLifetime, 0.1f);

    SightIndicatorActor = SpawnSightIndicatorConeByReflection(
        this,
        SightIndicatorDefinition,
        SightLocation,
        SightRotation,
        Lifetime,
        SafeHeight,
        SafeWidth);

    UpdateSightIndicatorTransform();
    UpdateSightIndicatorVisibility();
}

void ASecurityCameraEnemy::UpdateSightIndicatorTransform() const
{
    if (!IsValid(SightIndicatorActor) || !ShouldShowSightIndicator())
    {
        return;
    }

    const FVector SightLocation = (CameraMesh ? CameraMesh->GetComponentLocation() : GetActorLocation()) + FVector(0.0f, 0.0f, SightIndicatorZOffset);
    const FRotator SightRotation = GetActorRotation() + FRotator(0.0f, -90.0f, 0.0f);
    SightIndicatorActor->SetActorLocation(SightLocation);
    SightIndicatorActor->SetActorRotation(SightRotation);
}

void ASecurityCameraEnemy::DestroySightIndicator()
{
    if (IsValid(SightIndicatorActor))
    {
        SightIndicatorActor->Destroy();
    }
    SightIndicatorActor = nullptr;
}

void ASecurityCameraEnemy::UpdateSightIndicatorVisibility() const
{
    if (!IsValid(SightIndicatorActor))
    {
        return;
    }

    if (bHideSightIndicatorWhenNoVisualContact)
    {
        const bool bSelectedOverride =
#if WITH_EDITOR
            bShowSightIndicatorWhenSelected && IsSelectedInEditor();
#else
            false;
#endif
        SetSightIndicatorHiddenState(SightIndicatorActor, !(bPlayerInSight || bSelectedOverride));
    }
    else
    {
        SetSightIndicatorHiddenState(SightIndicatorActor, false);
    }
}
