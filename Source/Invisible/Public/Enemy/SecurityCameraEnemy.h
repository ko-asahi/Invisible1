#pragma once

#include "CoreMinimal.h"
#include "Enemy/AlertnessProvider.h"
#include "GameFramework/Actor.h"
#include "SecurityCameraEnemy.generated.h"

class UStaticMeshComponent;
class USceneComponent;
class UWidgetComponent;
class ASIZZ_DecalBaseActor;
class USIZZ_IndicatorBehaviourDefinition;

UCLASS()
class INVISIBLE_API ASecurityCameraEnemy : public AActor, public IAlertnessProvider
{
    GENERATED_BODY()

public:
    ASecurityCameraEnemy();

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void Tick(float DeltaSeconds) override;

public:
    virtual float GetAlertness_Implementation() const override { return Alertness; }
    virtual float GetAlertnessNormalized_Implementation() const override;

    UFUNCTION(BlueprintPure, Category = "SecurityCamera|Detection")
    bool IsPlayerInSight() const { return bPlayerInSight; }

    UFUNCTION(BlueprintCallable, Category = "SecurityCamera|Detection")
    void SetCameraDisabled(bool bDisabled);

    UFUNCTION(BlueprintPure, Category = "SecurityCamera|Detection")
    bool IsCameraDisabled() const { return bCameraDisabled; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SecurityCamera|Components")
    TObjectPtr<USceneComponent> Root = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SecurityCamera|Components")
    TObjectPtr<UStaticMeshComponent> CameraMesh = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SecurityCamera|Components")
    TObjectPtr<UWidgetComponent> AlertBarWidgetComp = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SecurityCamera|Detection", meta = (ClampMin = "0.0"))
    float SightRadius = 1200.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SecurityCamera|Detection", meta = (ClampMin = "0.0", ClampMax = "89.0"))
    float HalfViewAngle = 45.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SecurityCamera|Alert", meta = (ClampMin = "1.0"))
    float MaxAlertness = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SecurityCamera|Alert", meta = (ClampMin = "0.0"))
    float AlertGainRate = 30.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SecurityCamera|Alert", meta = (ClampMin = "0.0"))
    float AlertDecayRate = 20.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SecurityCamera|Alert")
    bool bDecayWhenPlayerLost = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SecurityCamera|GameOver", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "2.0"))
    float CameraGameOverDelay = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SecurityCamera|Detection", meta = (ClampMin = "0.02", ClampMax = "1.0", UIMin = "0.02", UIMax = "0.5"))
    float DetectionInterval = 0.1f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SecurityCamera|Debug")
    bool bDrawDebugSight = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SecurityCamera|VisualIndicator")
    bool bEnableSightIndicator = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SecurityCamera|VisualIndicator")
    bool bOnlyShowSightIndicatorInEditor = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SecurityCamera|VisualIndicator")
    USIZZ_IndicatorBehaviourDefinition* SightIndicatorDefinition = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SecurityCamera|VisualIndicator", meta = (ClampMin = "0.1"))
    float SightIndicatorLifetime = 99999.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SecurityCamera|VisualIndicator", meta = (ClampMin = "0.1", UIMin = "0.5", UIMax = "2.0"))
    float SightIndicatorHalfAngleScale = 1.2f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SecurityCamera|VisualIndicator", meta = (UIMin = "-500.0", UIMax = "500.0"))
    float SightIndicatorZOffset = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SecurityCamera|VisualIndicator")
    bool bHideSightIndicatorWhenNoVisualContact = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SecurityCamera|VisualIndicator")
    bool bShowSightIndicatorWhenSelected = true;

private:
    void EvaluateDetection();
    bool IsPlayerInSightInternal(float& OutDistance) const;
    void TriggerGameOver();
    void UpdateAlertWidgetVisibility() const;
    bool ShouldShowSightIndicator() const;
    void CreateSightIndicator();
    void UpdateSightIndicatorTransform() const;
    void DestroySightIndicator();
    void UpdateSightIndicatorVisibility() const;

private:
    FTimerHandle DetectionTimerHandle;

    UPROPERTY(Transient)
    TObjectPtr<ASIZZ_DecalBaseActor> SightIndicatorActor = nullptr;

    float Alertness = 0.0f;
    bool bPlayerInSight = false;
    bool bGameOverTriggered = false;
    bool bCameraDisabled = false;
};
