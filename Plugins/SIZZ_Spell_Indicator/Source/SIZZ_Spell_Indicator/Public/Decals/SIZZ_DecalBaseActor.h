// Copyright 2024, sizzoNNz, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "MaterialTypes.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "SIZZ_DecalBaseActor.generated.h"


// Scaling in Decal is swapped X with Z
// Decal size is 100x100 which should be 1m x 1m but actually its 2m x 2m? no idea why

class USIZZ_IndicatorBehaviourDefinition;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIndicatorFinishSignature,ASIZZ_DecalBaseActor*,Indicator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIndicatorStartSignature,ASIZZ_DecalBaseActor*,Indicator);


UCLASS(HideDropdown)
class SIZZ_SPELL_INDICATOR_API ASIZZ_DecalBaseActor : public ADecalActor
{
	GENERATED_BODY()

	friend class USIZZ_SpellIndicatorLibrary;
	
public:
	ASIZZ_DecalBaseActor();

	UPROPERTY(VisibleAnywhere,Category="Decal")
	TObjectPtr<UArrowComponent> ArrowForwardX;

/** Delegates */
	
	UPROPERTY(BlueprintAssignable,Category="Decal")
	FOnIndicatorFinishSignature OnIndicatorFinish;

	UPROPERTY(BlueprintAssignable,Category="Decal")
	FOnIndicatorFinishSignature OnIndicatorStart;

/** ~~ Delegates */

	
private:

	UPROPERTY(VisibleAnywhere,Category ="Decal")
	TObjectPtr<USceneComponent> DecalRoot;
	
	UPROPERTY(EditDefaultsOnly,Category ="Decal")
	float DecalHeight {100};

	UPROPERTY(EditAnywhere,Category ="Decal")
	FMaterialParameterInfo MaterialParameterInfo{};
	
	UPROPERTY()
	USIZZ_IndicatorBehaviourDefinition* DataIndicatorBehaviourDefinition{nullptr};
	
	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterial{nullptr};

	float CurrentMaterialValue{0};
	float RefreshRate{0.1};
	float RefreshValue{0.1};

	FTimerHandle StartIndicatorHandle;
	FTimerHandle IndicatorFinishTimer;
	FTimerHandle IndicatorUpdateValueTimer;
	
	UFUNCTION()
	void StartIndicator(float Time, USIZZ_IndicatorBehaviourDefinition* IndicatorDefinition, float IndicatorRefreshValue = 0.2);
	
	void SetDecalScale(float Radius);
	void SetDecalScale(float Height, float Width);
	void SetOffsetPosition(float Offset) const;
	void SetDecalRotation (const FRotator& Rotation);

	void CorrectBorderScaledSize() const;
	
	UFUNCTION()
	void UpdateIndicatorMaterial();

	UFUNCTION()
	void FinishIndicatorLifetime();

	UFUNCTION(BlueprintCallable,Category ="Decal")
	float GetCurrentValue() const {return CurrentMaterialValue;}
	
	void SetIndicatorMaterial(UMaterialInstanceDynamic* Material);
	float CalculateMaterialRefreshRate(float Time, float IndicatorRefreshValue);

	void FlipDecal() const;

};
