#include "Enemy/SecurityCameraEnemy.h"

#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Invisible_GameModeBase.h"
#include "Kismet/GameplayStatics.h"

ASecurityCameraEnemy::ASecurityCameraEnemy()
{
    PrimaryActorTick.bCanEverTick = false;

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

    Super::EndPlay(EndPlayReason);
}

float ASecurityCameraEnemy::GetAlertnessNormalized_Implementation() const
{
    return MaxAlertness > 0.0f ? Alertness / MaxAlertness : 0.0f;
}

void ASecurityCameraEnemy::EvaluateDetection()
{
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

    float Distance = 0.0f;
    const bool bInSight = IsPlayerInSightInternal(Distance);
    bPlayerInSight = bInSight;

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
