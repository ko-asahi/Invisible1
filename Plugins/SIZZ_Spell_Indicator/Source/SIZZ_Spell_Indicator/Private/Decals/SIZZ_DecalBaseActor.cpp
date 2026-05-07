// Copyright 2024, sizzoNNz, Inc. All Rights Reserved.

#include "Decals/SIZZ_DecalBaseActor.h"
#include "Components/ArrowComponent.h"
#include "Components/DecalComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Data/SIZZ_IndicatorBehaviourDefinition.h"

ASIZZ_DecalBaseActor::ASIZZ_DecalBaseActor()
{
	PrimaryActorTick.bCanEverTick = false;

	ArrowForwardX = CreateDefaultSubobject<UArrowComponent>(TEXT("ForwardXRotationArrow"));
	DecalRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(DecalRoot);
	GetDecal()->SetupAttachment(DecalRoot);
	ArrowForwardX->SetupAttachment(RootComponent);
	GetDecal()->DecalSize = {DecalHeight/2,50,50};
}

void ASIZZ_DecalBaseActor::StartIndicator(float Time, USIZZ_IndicatorBehaviourDefinition* IndicatorDefinition, float IndicatorRefreshValue)
{
	if(!GetWorld()) return;
	
	DataIndicatorBehaviourDefinition = IndicatorDefinition;
	RefreshRate = CalculateMaterialRefreshRate(Time,IndicatorRefreshValue);
	RefreshValue = IndicatorRefreshValue;


	// Start Indicator timer delegate
	GetWorld()->GetTimerManager().SetTimer(StartIndicatorHandle,
		FTimerDelegate::CreateLambda([&]
		{
			GetWorld()->GetTimerManager().ClearTimer(StartIndicatorHandle);
			OnIndicatorStart.Broadcast(this);
		}),IndicatorDefinition->Delay,false);


	GetWorld()->GetTimerManager().SetTimer(
		IndicatorFinishTimer,this,&ASIZZ_DecalBaseActor::FinishIndicatorLifetime,Time + IndicatorDefinition->Delay,false);
	
	// Finish Indicator timer delegate
	/*GetWorld()->GetTimerManager().SetTimer(
		IndicatorFinishTimer,
		FTimerDelegate::CreateLambda([&]
			{
				OnIndicatorFinish.Broadcast(this);
				GetWorld()->GetTimerManager().ClearTimer(IndicatorUpdateValueTimer);
				GetWorld()->GetTimerManager().ClearTimer(IndicatorFinishTimer);
			
				if(IsValid(this))
				{
					Destroy();
				}
			}
		),
		Time + IndicatorDefinition->Delay,false);*/

	// Update Indicator value
	GetWorld()->GetTimerManager().SetTimer(IndicatorUpdateValueTimer,
	this,&ASIZZ_DecalBaseActor::UpdateIndicatorMaterial,RefreshRate,true,IndicatorDefinition->Delay);
}

void ASIZZ_DecalBaseActor::FinishIndicatorLifetime()
{
	OnIndicatorFinish.Broadcast(this);
	GetWorld()->GetTimerManager().ClearTimer(IndicatorUpdateValueTimer);
	GetWorld()->GetTimerManager().ClearTimer(IndicatorFinishTimer);
			
	if(DataIndicatorBehaviourDefinition->LifeDuration == EIndicatorLifeDuration::Automatic && IsValid(this))
	{
		Destroy();
	}
}

void ASIZZ_DecalBaseActor::UpdateIndicatorMaterial()
{
	if(!DynamicMaterial) return;
	
	CurrentMaterialValue = FMath::Clamp(CurrentMaterialValue + RefreshValue,0,1);
	DynamicMaterial->SetScalarParameterValue(MaterialParameterInfo.Name,DataIndicatorBehaviourDefinition->IndicatorAnimationCurve->GetFloatValue(CurrentMaterialValue));
	
	//UE_LOG(LogTemp,Warning,TEXT("Curve value at %f is : %f"),CurrentMaterialValue,DataIndicatorBehaviourDefinition->IndicatorAnimationCurve->GetFloatValue(CurrentMaterialValue));
}



void ASIZZ_DecalBaseActor::SetDecalScale(float Radius)
{
	if (!GetDecal()) return;
	
	const double NewScale {Radius / GetDecal()->DecalSize.X};
	SetActorScale3D({NewScale,NewScale,NewScale});
}

void ASIZZ_DecalBaseActor::SetDecalScale(float Height, float Width)
{
	if (!GetDecal()) return;

	const double NewScaleX {Width / 100};
	const double NewScaleY {Height/ 100};

	SetActorScale3D({1,NewScaleY,NewScaleX});

	//UE_LOG(LogTemp,Error,TEXT("Scale X : %f , Scale Y : %f , Scale Z : %f"),1.0,NewScaleY,NewScaleX);
}

void ASIZZ_DecalBaseActor::SetOffsetPosition(float Offset) const
{
	float Divider {Offset * 2 / 100};
	GetDecal()->AddRelativeLocation({0,Offset/Divider,0});
}

void ASIZZ_DecalBaseActor::SetDecalRotation(const FRotator& Rotation)
{
	SetActorRotation(Rotation);
}

void ASIZZ_DecalBaseActor::CorrectBorderScaledSize() const
{
	DynamicMaterial->SetScalarParameterValue("BorderYScalar",GetActorScale().Y);
	DynamicMaterial->SetScalarParameterValue("BorderXScalar",GetActorScale().Z);

}

void ASIZZ_DecalBaseActor::SetIndicatorMaterial(UMaterialInstanceDynamic* Material) 
{
	if(!Material) return;
	GetDecal()->SetMaterial(0,Material);
	DynamicMaterial = Material;
}

float ASIZZ_DecalBaseActor::CalculateMaterialRefreshRate(float Time, float IndicatorRefreshValue)
{
	float x =  1 / IndicatorRefreshValue;
	return Time / x;
}

void ASIZZ_DecalBaseActor::FlipDecal() const
{
	GetDecal()->AddRelativeRotation({0,0,180});
}

