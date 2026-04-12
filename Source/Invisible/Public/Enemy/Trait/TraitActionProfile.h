// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "TraitActionProfile.generated.h"

/**
 * UTraitActionProfile 用于配置特质交互行为的默认值
 */


// 行为配置项
USTRUCT(BlueprintType)
struct FTraitActionProfileEntry
{
	GENERATED_BODY()

	// 行为Tag
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "Behavior.AI"))
	FGameplayTag BehaviorTag;

	// 默认的按键文本
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DefaultButtonText;

	// 默认的能量消耗
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0"))
	float DefaultEnergyCost = 0.0f;

	// 默认的执行距离
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0"))
	float DefaultExecutionRadius = 150.0f;

	// 默认的行为持续时长
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0"))
	float DefaultDuration = 10.0f;
};


UCLASS()
class INVISIBLE_API UTraitActionProfile : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trait|Action")
	TArray<FTraitActionProfileEntry> ActionProfileEntries;

	// 根据行为Tag查找行为配置项
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Trait|Action")
	bool FindActionProfile(FGameplayTag BehaviorTag, FTraitActionProfileEntry& OutEntry) const;

	
};
