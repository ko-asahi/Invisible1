#include "Interaction/SlidingDoor.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy/EnemyBase.h"
#include "GameFramework/Pawn.h"
#include "Interaction/InteractionTargetComponent.h"
#include "InvisiblePlayerState.h"
#include "NavigationSystem.h"
#include "Player/PlayerCharacter.h"

ASlidingDoor::ASlidingDoor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(SceneRoot);
	DoorMesh->SetMobility(EComponentMobility::Movable);
	DoorMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DoorMesh->SetCollisionObjectType(ECC_WorldDynamic);
	DoorMesh->SetCollisionResponseToAllChannels(ECR_Block);
	DoorMesh->SetCanEverAffectNavigation(true);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(SceneRoot);
	TriggerBox->SetBoxExtent(FVector(220.0f, 220.0f, 160.0f));
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECC_WorldDynamic);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	TriggerBox->SetCanEverAffectNavigation(false);

	OpenDirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("OpenDirectionArrow"));
	OpenDirectionArrow->SetupAttachment(SceneRoot);
	OpenDirectionArrow->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	InteractionTargetComponent = CreateDefaultSubobject<UInteractionTargetComponent>(TEXT("InteractionTargetComponent"));
	const FGameplayTag DoorTargetTag = FGameplayTag::RequestGameplayTag(TEXT("Interaction.Target.Door"), false);
	if (DoorTargetTag.IsValid())
	{
		InteractionTargetComponent->InteractionTargetTags.AddTag(DoorTargetTag);
	}
}

void ASlidingDoor::BeginPlay()
{
	Super::BeginPlay();

	bIsLocked = bStartsLocked;
	ClosedRelativeLocation = DoorMesh->GetRelativeLocation();
	RecalculateOpenLocation();
	DoorState = bIsLocked ? ESlidingDoorState::Locked : ESlidingDoorState::Closed;

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASlidingDoor::HandleTriggerBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ASlidingDoor::HandleTriggerEndOverlap);
	SetDoorCollisionOpen(false);
}

void ASlidingDoor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(CloseDelayTimerHandle);
	}

	Super::EndPlay(EndPlayReason);
}

void ASlidingDoor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateDoorMovement(DeltaSeconds);
}

bool ASlidingDoor::TryOpenDoor(AActor* InstigatorActor)
{
	if (!CanActorTriggerDoor(InstigatorActor))
	{
		return false;
	}

	if (bIsLocked)
	{
		if (!CanActorUnlockDoor(InstigatorActor))
		{
			BP_OnDoorLocked(InstigatorActor);
			return false;
		}

		UnlockDoor();
	}

	StartOpening(InstigatorActor);
	return true;
}

void ASlidingDoor::CloseDoor()
{
	RefreshOpeners();
	if (HasActiveOpeners())
	{
		return;
	}

	StartClosing();
}

void ASlidingDoor::UnlockDoor()
{
	bIsLocked = false;
	if (DoorState == ESlidingDoorState::Locked)
	{
		DoorState = ESlidingDoorState::Closed;
	}
}

void ASlidingDoor::LockDoor()
{
	bIsLocked = true;
	if (DoorAlpha <= KINDA_SMALL_NUMBER)
	{
		DoorState = ESlidingDoorState::Locked;
	}
}

void ASlidingDoor::HandleTriggerBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (!CanActorTriggerDoor(OtherActor))
	{
		return;
	}

	ActiveOpeners.AddUnique(TWeakObjectPtr<AActor>(OtherActor));
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(CloseDelayTimerHandle);
	}

	TryOpenDoor(OtherActor);
}

void ASlidingDoor::HandleTriggerEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	ActiveOpeners.Remove(TWeakObjectPtr<AActor>(OtherActor));
	ScheduleCloseIfNoOpeners();
}

void ASlidingDoor::StartOpening(AActor* InstigatorActor)
{
	if (bUnlockPermanentlyWhenOpened)
	{
		bIsLocked = false;
	}

	RecalculateOpenLocation();
	TargetDoorAlpha = 1.0f;
	DoorState = ESlidingDoorState::Opening;
	SetActorTickEnabled(true);
	BP_OnDoorStartedOpening(InstigatorActor);
}

void ASlidingDoor::StartClosing()
{
	if (DoorAlpha <= KINDA_SMALL_NUMBER)
	{
		DoorAlpha = 0.0f;
		DoorMesh->SetRelativeLocation(ClosedRelativeLocation);
		DoorState = bIsLocked ? ESlidingDoorState::Locked : ESlidingDoorState::Closed;
		SetActorTickEnabled(false);
		SetDoorCollisionOpen(false);
		return;
	}

	TargetDoorAlpha = 0.0f;
	DoorState = ESlidingDoorState::Closing;
	SetActorTickEnabled(true);
	BP_OnDoorStartedClosing();
}

void ASlidingDoor::UpdateDoorMovement(float DeltaSeconds)
{
	if (FMath::IsNearlyEqual(DoorAlpha, TargetDoorAlpha, KINDA_SMALL_NUMBER))
	{
		SetActorTickEnabled(false);
		return;
	}

	const float SafeDuration = FMath::Max(SlideDuration, 0.01f);
	const float Step = DeltaSeconds / SafeDuration;
	DoorAlpha = FMath::FInterpConstantTo(DoorAlpha, TargetDoorAlpha, DeltaSeconds, 1.0f / SafeDuration);
	DoorAlpha = FMath::Clamp(DoorAlpha, 0.0f, 1.0f);

	DoorMesh->SetRelativeLocation(FMath::Lerp(ClosedRelativeLocation, OpenRelativeLocation, DoorAlpha));

	const bool bShouldDisableOpenCollision = DoorAlpha >= OpenCollisionDisableAlpha;
	if (bDisablePawnCollisionWhenOpen && bShouldDisableOpenCollision != bOpenCollisionDisabled)
	{
		SetDoorCollisionOpen(bShouldDisableOpenCollision);
	}

	if (FMath::IsNearlyEqual(DoorAlpha, TargetDoorAlpha, Step + KINDA_SMALL_NUMBER))
	{
		DoorAlpha = TargetDoorAlpha;
		DoorMesh->SetRelativeLocation(FMath::Lerp(ClosedRelativeLocation, OpenRelativeLocation, DoorAlpha));

		if (DoorAlpha >= 1.0f - KINDA_SMALL_NUMBER)
		{
			SetDoorCollisionOpen(true);
			DoorState = ESlidingDoorState::Open;
			BP_OnDoorOpened();
		}
		else
		{
			SetDoorCollisionOpen(false);
			DoorState = bIsLocked ? ESlidingDoorState::Locked : ESlidingDoorState::Closed;
			BP_OnDoorClosed();
		}

		SetActorTickEnabled(false);
	}
}

void ASlidingDoor::RecalculateOpenLocation()
{
	FVector LocalDirection = FVector::ZeroVector;
	switch (OpenDirection)
	{
	case ESlidingDoorOpenDirection::Left:
		LocalDirection = FVector(0.0f, -1.0f, 0.0f);
		break;
	case ESlidingDoorOpenDirection::Right:
		LocalDirection = FVector(0.0f, 1.0f, 0.0f);
		break;
	case ESlidingDoorOpenDirection::Custom:
		LocalDirection = CustomOpenDirectionLocal;
		break;
	default:
		LocalDirection = FVector(0.0f, 1.0f, 0.0f);
		break;
	}

	if (LocalDirection.IsNearlyZero())
	{
		LocalDirection = FVector(0.0f, 1.0f, 0.0f);
	}

	OpenRelativeLocation = ClosedRelativeLocation + LocalDirection.GetSafeNormal() * FMath::Max(0.0f, SlideDistance);
}

void ASlidingDoor::RefreshOpeners()
{
	for (int32 Index = ActiveOpeners.Num() - 1; Index >= 0; --Index)
	{
		AActor* Actor = ActiveOpeners[Index].Get();
		if (!Actor || !CanActorTriggerDoor(Actor) || !TriggerBox->IsOverlappingActor(Actor))
		{
			ActiveOpeners.RemoveAtSwap(Index);
		}
	}
}

void ASlidingDoor::ScheduleCloseIfNoOpeners()
{
	RefreshOpeners();
	if (HasActiveOpeners())
	{
		return;
	}

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(CloseDelayTimerHandle);
		World->GetTimerManager().SetTimer(
			CloseDelayTimerHandle,
			this,
			&ASlidingDoor::CloseDoor,
			FMath::Max(CloseDelay, 0.0f),
			false);
	}
}

void ASlidingDoor::SetDoorCollisionOpen(bool bOpenForNavigation)
{
	bOpenCollisionDisabled = bOpenForNavigation;

	if (bDisablePawnCollisionWhenOpen && bOpenForNavigation)
	{
		DoorMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		DoorMesh->SetCanEverAffectNavigation(false);
	}
	else
	{
		DoorMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		DoorMesh->SetCanEverAffectNavigation(true);
	}

	RefreshNavigation();
}

void ASlidingDoor::RefreshNavigation()
{
	if (UWorld* World = GetWorld())
	{
		if (UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World))
		{
			NavSys->UpdateActorInNavOctree(*this);
		}
	}
}

bool ASlidingDoor::CanActorTriggerDoor(AActor* Actor) const
{
	if (!Actor)
	{
		return false;
	}

	if (bAutoOpenForPlayer && Actor->IsA<APlayerCharacter>())
	{
		return true;
	}

	return bAutoOpenForAI && Actor->IsA<AEnemyBase>();
}

bool ASlidingDoor::CanActorUnlockDoor(AActor* Actor) const
{
	if (!RequiredKeyCardTag.IsValid())
	{
		return true;
	}

	if (bAllowAIToOpenLockedDoor && Actor && Actor->IsA<AEnemyBase>())
	{
		return true;
	}

	APawn* Pawn = Cast<APawn>(Actor);
	const AInvisiblePlayerState* InvisiblePlayerState = Pawn ? Pawn->GetPlayerState<AInvisiblePlayerState>() : nullptr;
	return InvisiblePlayerState && InvisiblePlayerState->HasKeyCard(RequiredKeyCardTag);
}

bool ASlidingDoor::HasActiveOpeners() const
{
	return ActiveOpeners.Num() > 0;
}
