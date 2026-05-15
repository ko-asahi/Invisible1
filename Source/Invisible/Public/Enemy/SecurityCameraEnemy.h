#pragma once

#include "CoreMinimal.h"
#include "Enemy/AlertnessProvider.h"
#include "GameFramework/Actor.h"
#include "SecurityCameraEnemy.generated.h"

class UStaticMeshComponent;
class USceneComponent;
class UWidgetComponent;

UCLASS()
class INVISIBLE_API ASecurityCameraEnemy : public AActor, public IAlertnessProvider
{
    GENERATED_BODY()

public:
    ASecurityCameraEnemy();

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    virtual float GetAlertness_Implementation() const override { return Alertness; }
    virtual float GetAlertnessNormalized_Implementation() const override;

    UFUNCTION(BlueprintPure, Category = "SecurityCamera|Detection")
    bool IsPlayerInSight() const { return bPlayerInSight; }

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

private:
    void EvaluateDetection();
    bool IsPlayerInSightInternal(float& OutDistance) const;
    void TriggerGameOver();
    void UpdateAlertWidgetVisibility() const;

private:
    FTimerHandle DetectionTimerHandle;

    float Alertness = 0.0f;
    bool bPlayerInSight = false;
    bool bGameOverTriggered = false;
};
