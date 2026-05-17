#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraPowerSwitch.generated.h"

class APawn;
class UBoxComponent;
class UStaticMeshComponent;
class USceneComponent;
class UWidgetComponent;
class UUserWidget;

UCLASS(Blueprintable)
class INVISIBLE_API ACameraPowerSwitch : public AActor
{
    GENERATED_BODY()

public:
    ACameraPowerSwitch();

    UFUNCTION(BlueprintCallable, Category = "CameraSwitch")
    bool TryActivateSwitch(APawn* InstigatorPawn);

    UFUNCTION(BlueprintPure, Category = "CameraSwitch")
    bool CanBeActivatedByPawn(const APawn* Pawn) const;

    UFUNCTION(BlueprintPure, Category = "CameraSwitch")
    bool IsActivated() const { return bActivated; }

    UFUNCTION(BlueprintPure, Category = "CameraSwitch")
    float GetInteractionRadius() const { return InteractionRadius; }

    UFUNCTION(BlueprintPure, Category = "CameraSwitch")
    FText GetInteractHintText() const { return InteractHintText; }

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<USceneComponent> Root = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> SwitchMesh = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UBoxComponent> InteractionTrigger = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UWidgetComponent> PromptWidgetComp = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UUserWidget> InteractionPromptWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (ClampMin = "50.0"))
    float InteractionRadius = 180.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    FVector WidgetOffset = FVector(0.0f, 0.0f, 140.0f);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    FText InteractHintText = FText::FromString(TEXT("按E关闭监控"));

    UFUNCTION(BlueprintImplementableEvent, Category = "CameraSwitch")
    void BP_OnSwitchActivated(APawn* InstigatorPawn, int32 DisabledCameraCount);

private:
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

    bool IsPawnInRange(const APawn* Pawn) const;
    void UpdatePromptVisibility();

private:
    UPROPERTY(Transient)
    bool bActivated = false;

    UPROPERTY(Transient)
    TSet<TWeakObjectPtr<APawn>> OverlappingPawns;
};

