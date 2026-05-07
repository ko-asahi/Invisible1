// Copyright 2024, sizzoNNz, Inc. All Rights Reserved.


#include "SpellIndicatorLibrary/SIZZ_SpellIndicatorLibrary.h"
#include "Engine/World.h"
#include "Data/SIZZ_CustomIndicatorRefreshValue.h"
#include "Data/SIZZ_IndicatorBehaviourDefinition.h"
#include "Decals/SIZZ_DecalBaseActor.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetMathLibrary.h"

ASIZZ_DecalBaseActor* USIZZ_SpellIndicatorLibrary::SpawnIndicatorRect(UObject* WorldObjContext,USIZZ_IndicatorBehaviourDefinition* IndicatorDefinition,const FVector& Position,const FRotator& Rotation,float Time, float YawRotation, float Height, float Width, bool bOffsetByWidth)
{
	if(!WorldObjContext) return nullptr;
	UWorld* World = WorldObjContext->GetWorld();
	if(!World) return nullptr;

	checkf(Height > 0,TEXT("Height can't be set to negative or 0 value"))
	checkf(Width > 0,TEXT("Width can't be set to negative or 0 value"))
	checkf(Time > 0,TEXT("Indicator Time can't be set to negative or 0 value"))
	checkf(IndicatorDefinition->IndicatorClassToSpawn,TEXT("Indicator Class to spawn is not set inside "))
	checkf(IndicatorDefinition->IndicatorMaterial,TEXT("Indicator Material is not set inside "))
	checkf(IndicatorDefinition->IndicatorAnimationCurve,TEXT("Indicator Animation Curve is not set set inside"))
	checkf(IndicatorDefinition->RefreshData,TEXT("Refresh Data is not set set inside"))
	checkf(IndicatorDefinition->RefreshData->RefreshValue >= 0 ,TEXT("Refresh Value can't be less or equal 0"))

	const FTransform Transform {Position};
	
	ASIZZ_DecalBaseActor* SpawnedDecal = World->SpawnActorDeferred<ASIZZ_DecalBaseActor>(IndicatorDefinition->IndicatorClassToSpawn,Transform);
	SpawnedDecal->SetDecalScale(Height,Width);

	if(bOffsetByWidth)
	{
		SpawnedDecal->SetOffsetPosition(Height/2);
	}

	SpawnedDecal->SetDecalRotation(UKismetMathLibrary::ComposeRotators({0,-90,0}, Rotation));
	SpawnedDecal->SetIndicatorMaterial(UKismetMaterialLibrary::CreateDynamicMaterialInstance(WorldObjContext,IndicatorDefinition->IndicatorMaterial));
	SpawnedDecal->StartIndicator(Time,IndicatorDefinition,IndicatorDefinition->RefreshData->RefreshValue);
	SpawnedDecal->CorrectBorderScaledSize();
	SpawnedDecal->FinishSpawning(Transform);
	return SpawnedDecal;
}

ASIZZ_DecalBaseActor* USIZZ_SpellIndicatorLibrary::SpawnIndicatorCone(UObject* WorldObjContext,USIZZ_IndicatorBehaviourDefinition* IndicatorDefinition, const FVector& Position, const FRotator& Rotation,float Time, float Height, float Width, bool bOffsetByWidth,bool bFlipCone)
{
	if(!WorldObjContext) return nullptr;
	UWorld* World = WorldObjContext->GetWorld();
	if(!World) return nullptr;

	checkf(Height > 0,TEXT("Height can't be set to negative or 0 value"))
	checkf(Width > 0,TEXT("Width can't be set to negative or 0 value"))
	checkf(Time > 0,TEXT("Indicator Time can't be set to negative or 0 value"))
	checkf(IndicatorDefinition->IndicatorClassToSpawn,TEXT("Indicator Class to spawn is not set inside "))
	checkf(IndicatorDefinition->IndicatorMaterial,TEXT("Indicator Material is not set inside "))
	checkf(IndicatorDefinition->IndicatorAnimationCurve,TEXT("Indicator Animation Curve is not set set inside"))
	checkf(IndicatorDefinition->RefreshData,TEXT("Refresh Data is not set set inside"))
	checkf(IndicatorDefinition->RefreshData->RefreshValue >= 0 ,TEXT("Refresh Value can't be less or equal 0"))

	
	const FTransform Transform {Position};
	
	ASIZZ_DecalBaseActor* SpawnedDecal = World->SpawnActorDeferred<ASIZZ_DecalBaseActor>(IndicatorDefinition->IndicatorClassToSpawn,Transform);
	SpawnedDecal->SetDecalScale(Height,Width);

	if(bOffsetByWidth)
	{
		SpawnedDecal->SetOffsetPosition(Height/2);
	}

	// Cone material is flipped by default, it's actually reverting the flip but this way it's easier for ppl to understand
	if(!bFlipCone)
	{
		SpawnedDecal->FlipDecal();
	}
	
	SpawnedDecal->SetDecalRotation(UKismetMathLibrary::ComposeRotators({0,-90,0}, Rotation));
	SpawnedDecal->SetIndicatorMaterial(UKismetMaterialLibrary::CreateDynamicMaterialInstance(WorldObjContext,IndicatorDefinition->IndicatorMaterial));
	SpawnedDecal->StartIndicator(Time,IndicatorDefinition,IndicatorDefinition->RefreshData->RefreshValue); 
	SpawnedDecal->FinishSpawning(Transform);
	return SpawnedDecal;

	
}

ASIZZ_DecalBaseActor* USIZZ_SpellIndicatorLibrary::SpawnIndicatorCircle(UObject* WorldObjContext,USIZZ_IndicatorBehaviourDefinition* IndicatorDefinition, const FVector& Position, float Time, float Radius)
{
	if(!WorldObjContext) return nullptr;
	UWorld* World = WorldObjContext->GetWorld();
	if(!World) return nullptr;

	checkf(Radius > 0,TEXT("Indicator Radius can't be set to negative or 0 value"))
	checkf(IndicatorDefinition,TEXT("Indicator Definition is not set"))
	checkf(IndicatorDefinition->IndicatorClassToSpawn,TEXT("Indicator Class to spawn is not set inside "))
	checkf(IndicatorDefinition->IndicatorMaterial,TEXT("Indicator Material is not set inside "))
	checkf(IndicatorDefinition->IndicatorAnimationCurve,TEXT("Indicator Animation Curve is not set set inside"))
	checkf(IndicatorDefinition->RefreshData,TEXT("Refresh Data is not set set inside"))
	checkf(IndicatorDefinition->RefreshData->RefreshValue >= 0 ,TEXT("Refresh Value can't be less or equal 0"))

	
	const FTransform Transform {Position};
	
	ASIZZ_DecalBaseActor* SpawnedDecal = World->SpawnActorDeferred<ASIZZ_DecalBaseActor>(IndicatorDefinition->IndicatorClassToSpawn,Transform);
	SpawnedDecal->SetDecalScale(Radius);
	SpawnedDecal->SetIndicatorMaterial(UKismetMaterialLibrary::CreateDynamicMaterialInstance(WorldObjContext,IndicatorDefinition->IndicatorMaterial));
	SpawnedDecal->StartIndicator(Time,IndicatorDefinition,IndicatorDefinition->RefreshData->RefreshValue); 
	SpawnedDecal->FinishSpawning(Transform);
	return SpawnedDecal;
}
