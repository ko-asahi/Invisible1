// Copyright 2024, sizzoNNz, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Curves/CurveFloat.h"
#include "Materials/MaterialInstance.h"
#include "Decals/SIZZ_DecalBaseActor.h"
#include "SIZZ_IndicatorBehaviourDefinition.generated.h"

class USIZZ_CustomIndicatorRefreshValue;

UENUM()
enum class EIndicatorLifeDuration
{
	Automatic,
	Manual,
};

UCLASS()
class SIZZ_SPELL_INDICATOR_API USIZZ_IndicatorBehaviourDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,Category ="Indicator")
	UCurveFloat* IndicatorAnimationCurve{nullptr}; 

	UPROPERTY(EditAnywhere,Category ="Indicator")
	UMaterialInstance* IndicatorMaterial{nullptr};

	UPROPERTY(EditAnywhere,Category = "Indicator")
	TSubclassOf<ASIZZ_DecalBaseActor> IndicatorClassToSpawn{nullptr};
	
	UPROPERTY(EditAnywhere,Category ="Indicator")
	float Delay{-1};

	UPROPERTY(EditAnywhere,Category ="Indicator")
	USIZZ_CustomIndicatorRefreshValue* RefreshData{nullptr};

	/** Automatic Duration = Once indicator animation end it will be destroyed,
	 * Manual = Indicator has to be explicitly destroyed, by Destroy();
	 */
	UPROPERTY(EditAnywhere,Category ="Indicator")
	EIndicatorLifeDuration LifeDuration{EIndicatorLifeDuration::Automatic};
	
};
