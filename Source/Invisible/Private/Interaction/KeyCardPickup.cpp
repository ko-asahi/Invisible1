#include "Interaction/KeyCardPickup.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "InvisiblePlayerState.h"

AKeyCardPickup::AKeyCardPickup()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	KeyCardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyCardMesh"));
	KeyCardMesh->SetupAttachment(SceneRoot);
	KeyCardMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickupSphere"));
	PickupSphere->SetupAttachment(SceneRoot);
	PickupSphere->SetSphereRadius(120.0f);
	PickupSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupSphere->SetCollisionObjectType(ECC_WorldDynamic);
	PickupSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AKeyCardPickup::BeginPlay()
{
	Super::BeginPlay();

	PickupSphere->OnComponentBeginOverlap.AddDynamic(this, &AKeyCardPickup::HandlePickupSphereBeginOverlap);
}

void AKeyCardPickup::HandlePickupSphereBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	APawn* Pawn = Cast<APawn>(OtherActor);
	if (!Pawn || bPickedUp)
	{
		return;
	}

	TryGiveKeyCardToPawn(Pawn);
}

bool AKeyCardPickup::TryGiveKeyCardToPawn(APawn* Pawn)
{
	if (!Pawn || !KeyCardTag.IsValid())
	{
		return false;
	}

	AInvisiblePlayerState* InvisiblePlayerState = Pawn->GetPlayerState<AInvisiblePlayerState>();
	if (!InvisiblePlayerState)
	{
		return false;
	}

	bPickedUp = true;
	InvisiblePlayerState->AddKeyCard(KeyCardTag);
	BP_OnPickedUp(Pawn, KeyCardTag);

	PickupSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	KeyCardMesh->SetVisibility(false, true);

	if (bDestroyOnPickup)
	{
		Destroy();
	}

	return true;
}
