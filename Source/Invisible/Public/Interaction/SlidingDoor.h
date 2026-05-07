#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "SlidingDoor.generated.h"

class UArrowComponent;
class UBoxComponent;
class UInteractionTargetComponent;
class UStaticMeshComponent;

UENUM(BlueprintType)
enum class ESlidingDoorOpenDirection : uint8
{
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right"),
	Custom UMETA(DisplayName = "Custom")
};

UENUM(BlueprintType)
enum class ESlidingDoorState : uint8
{
	Closed UMETA(DisplayName = "Closed"),
	Opening UMETA(DisplayName = "Opening"),
	Open UMETA(DisplayName = "Open"),
	Closing UMETA(DisplayName = "Closing"),
	Locked UMETA(DisplayName = "Locked")
};

UCLASS(Blueprintable)
class INVISIBLE_API ASlidingDoor : public AActor
{
	GENERATED_BODY()

public:
	ASlidingDoor();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Door")
	bool TryOpenDoor(AActor* InstigatorActor);

	UFUNCTION(BlueprintCallable, Category = "Door")
	void CloseDoor();

	UFUNCTION(BlueprintCallable, Category = "Door")
	void UnlockDoor();

	UFUNCTION(BlueprintCallable, Category = "Door")
	void LockDoor();

	UFUNCTION(BlueprintPure, Category = "Door")
	bool IsOpen() const { return DoorAlpha >= 1.0f - KINDA_SMALL_NUMBER; }

	UFUNCTION(BlueprintPure, Category = "Door")
	bool IsLocked() const { return bIsLocked; }

	UFUNCTION(BlueprintPure, Category = "Door")
	ESlidingDoorState GetDoorState() const { return DoorState; }

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> DoorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> TriggerBox;

	// 给编辑器中配置滑动方向做可视化提示。
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UArrowComponent> OpenDirectionArrow;

	// 让编辑模式 AI_With_Object 交互可以识别这扇门；不需要时可在蓝图里关闭。
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UInteractionTargetComponent> InteractionTargetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door|Motion")
	ESlidingDoorOpenDirection OpenDirection = ESlidingDoorOpenDirection::Right;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door|Motion", meta = (EditCondition = "OpenDirection == ESlidingDoorOpenDirection::Custom"))
	FVector CustomOpenDirectionLocal = FVector(0.0f, 1.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door|Motion", meta = (ClampMin = "0.0"))
	float SlideDistance = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door|Motion", meta = (ClampMin = "0.01"))
	float SlideDuration = 0.75f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door|Motion", meta = (ClampMin = "0.0"))
	float CloseDelay = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door|Access")
	bool bStartsLocked = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door|Access", meta = (Categories = "KeyCard"))
	FGameplayTag RequiredKeyCardTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door|Access")
	bool bUnlockPermanentlyWhenOpened = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door|Access")
	bool bAllowAIToOpenLockedDoor = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door|Trigger")
	bool bAutoOpenForPlayer = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door|Trigger")
	bool bAutoOpenForAI = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door|Navigation")
	bool bDisablePawnCollisionWhenOpen = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door|Navigation", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float OpenCollisionDisableAlpha = 0.8f;

	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void BP_OnDoorStartedOpening(AActor* InstigatorActor);

	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void BP_OnDoorOpened();

	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void BP_OnDoorStartedClosing();

	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void BP_OnDoorClosed();

	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void BP_OnDoorLocked(AActor* InstigatorActor);

private:
	UPROPERTY(Transient)
	ESlidingDoorState DoorState = ESlidingDoorState::Closed;

	UPROPERTY(Transient)
	bool bIsLocked = false;

	FVector ClosedRelativeLocation = FVector::ZeroVector;
	FVector OpenRelativeLocation = FVector::ZeroVector;
	float DoorAlpha = 0.0f;
	float TargetDoorAlpha = 0.0f;
	bool bOpenCollisionDisabled = false;
	FTimerHandle CloseDelayTimerHandle;
	TArray<TWeakObjectPtr<AActor>> ActiveOpeners;

	UFUNCTION()
	void HandleTriggerBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void HandleTriggerEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	void StartOpening(AActor* InstigatorActor);
	void StartClosing();
	void UpdateDoorMovement(float DeltaSeconds);
	void RecalculateOpenLocation();
	void RefreshOpeners();
	void ScheduleCloseIfNoOpeners();
	void SetDoorCollisionOpen(bool bOpenForNavigation);
	void RefreshNavigation();
	bool CanActorTriggerDoor(AActor* Actor) const;
	bool CanActorUnlockDoor(AActor* Actor) const;
	bool HasActiveOpeners() const;
};
