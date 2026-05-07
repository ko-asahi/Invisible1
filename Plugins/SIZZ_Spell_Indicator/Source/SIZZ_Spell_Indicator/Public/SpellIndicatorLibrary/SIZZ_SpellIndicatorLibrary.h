// Copyright 2024, sizzoNNz, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SIZZ_SpellIndicatorLibrary.generated.h"



class ASIZZ_DecalBaseActor;
class USIZZ_IndicatorBehaviourDefinition;
/**
 * 
 */
UCLASS()
class SIZZ_SPELL_INDICATOR_API USIZZ_SpellIndicatorLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable,Category ="SpellIndicator",meta=(DefaultToSelf = "WorldObjContext",HidePin="WorldObjContext"))
	static ASIZZ_DecalBaseActor* SpawnIndicatorRect(UObject* WorldObjContext,USIZZ_IndicatorBehaviourDefinition* IndicatorDefinition, const FVector& Position,const FRotator& Rotation = FRotator::ZeroRotator, float Time = 1, float YawRotation = 0, float Height = 100, float Width = 100, bool bOffsetByWidth = true);

	UFUNCTION(BlueprintCallable,Category ="SpellIndicator",meta=(DefaultToSelf = "WorldObjContext",HidePin="WorldObjContext"))
	static ASIZZ_DecalBaseActor* SpawnIndicatorCone(UObject* WorldObjContext,USIZZ_IndicatorBehaviourDefinition* IndicatorDefinition, const FVector& Position,const FRotator& Rotation = FRotator::ZeroRotator, float Time = 1, float Height = 100, float Width = 100, bool bOffsetByWidth = true, bool bFlipCone = false);
	
	UFUNCTION(BlueprintCallable,Category ="SpellIndicator",meta=(DefaultToSelf = "WorldObjContext",HidePin="WorldObjContext"))
	static ASIZZ_DecalBaseActor* SpawnIndicatorCircle(UObject* WorldObjContext,USIZZ_IndicatorBehaviourDefinition* IndicatorDefinition,const FVector& Position,float Time = 1,float Radius = 100);

};
