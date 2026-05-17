#include "Interaction/CameraPowerSwitch.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Enemy/SecurityCameraEnemy.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

ACameraPowerSwitch::ACameraPowerSwitch()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);

    SwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwitchMesh"));
    SwitchMesh->SetupAttachment(Root);
    SwitchMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    SwitchMesh->SetCollisionObjectType(ECC_WorldDynamic);
    SwitchMesh->SetCollisionResponseToAllChannels(ECR_Block);

    InteractionTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionTrigger"));
    InteractionTrigger->SetupAttachment(Root);
    InteractionTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    InteractionTrigger->SetCollisionObjectType(ECC_WorldDynamic);
    InteractionTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
    InteractionTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    InteractionTrigger->SetCanEverAffectNavigation(false);

    PromptWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("PromptWidgetComp"));
    PromptWidgetComp->SetupAttachment(Root);
    PromptWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
    PromptWidgetComp->SetDrawAtDesiredSize(true);
    PromptWidgetComp->SetPivot(FVector2D(0.5f, 1.0f));
    PromptWidgetComp->SetVisibility(false);
}

void ACameraPowerSwitch::BeginPlay()
{
    Super::BeginPlay();

    const FVector Extent(InteractionRadius, InteractionRadius, 120.0f);
    InteractionTrigger->SetBoxExtent(Extent);
    PromptWidgetComp->SetRelativeLocation(WidgetOffset);

    if (InteractionPromptWidgetClass)
    {
        PromptWidgetComp->SetWidgetClass(InteractionPromptWidgetClass);
    }

    InteractionTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACameraPowerSwitch::HandleTriggerBeginOverlap);
    InteractionTrigger->OnComponentEndOverlap.AddDynamic(this, &ACameraPowerSwitch::HandleTriggerEndOverlap);

    UpdatePromptVisibility();
}

bool ACameraPowerSwitch::TryActivateSwitch(APawn* InstigatorPawn)
{
    if (!CanBeActivatedByPawn(InstigatorPawn))
    {
        return false;
    }

    bActivated = true;
    UpdatePromptVisibility();
    InteractionTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    OverlappingPawns.Reset();

    TArray<AActor*> FoundCameras;
    UGameplayStatics::GetAllActorsOfClass(this, ASecurityCameraEnemy::StaticClass(), FoundCameras);

    int32 DisabledCameraCount = 0;
    for (AActor* CameraActor : FoundCameras)
    {
        ASecurityCameraEnemy* CameraEnemy = Cast<ASecurityCameraEnemy>(CameraActor);
        if (!CameraEnemy)
        {
            continue;
        }

        CameraEnemy->SetCameraDisabled(true);
        ++DisabledCameraCount;
    }

    BP_OnSwitchActivated(InstigatorPawn, DisabledCameraCount);
    return true;
}

bool ACameraPowerSwitch::CanBeActivatedByPawn(const APawn* Pawn) const
{
    if (bActivated || !Pawn)
    {
        return false;
    }

    return IsPawnInRange(Pawn);
}

void ACameraPowerSwitch::HandleTriggerBeginOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    APawn* OverlapPawn = Cast<APawn>(OtherActor);
    if (!OverlapPawn || bActivated)
    {
        return;
    }

    OverlappingPawns.Add(OverlapPawn);
    UpdatePromptVisibility();
}

void ACameraPowerSwitch::HandleTriggerEndOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex)
{
    APawn* OverlapPawn = Cast<APawn>(OtherActor);
    if (!OverlapPawn)
    {
        return;
    }

    OverlappingPawns.Remove(OverlapPawn);
    UpdatePromptVisibility();
}

bool ACameraPowerSwitch::IsPawnInRange(const APawn* Pawn) const
{
    if (!Pawn)
    {
        return false;
    }

    const float DistSq = FVector::DistSquared2D(Pawn->GetActorLocation(), GetActorLocation());
    return DistSq <= FMath::Square(InteractionRadius);
}

void ACameraPowerSwitch::UpdatePromptVisibility()
{
    if (!PromptWidgetComp)
    {
        return;
    }

    if (bActivated)
    {
        PromptWidgetComp->SetVisibility(false);
        return;
    }

    OverlappingPawns.Remove(nullptr);
    PromptWidgetComp->SetVisibility(OverlappingPawns.Num() > 0);
}

