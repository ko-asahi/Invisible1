// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Enemy/Trait/TraitDefinition.h"
#include "Enemy/Trait/TraitActionProfile.h"
#include "TraitActionResolver.generated.h"

/**
 * TraitActionResolver是一个特质行为解析器，用于获取特质行为的配置，在有新规则存在时进行覆盖，否则使用默认配置
 */

USTRUCT(BlueprintType)
struct FTraitResolvedAction
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	bool bValid = false;

	UPROPERTY(BlueprintReadOnly, meta = (Categories = "Behavior.AI"))
	FGameplayTag ActionTag;

	UPROPERTY(BlueprintReadOnly)
	FText ButtonText;

	UPROPERTY(BlueprintReadOnly)
	float EnergyCost = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	float ExecutionRadius = 150.0f;

	UPROPERTY(BlueprintReadOnly)
	float Duration = 10.0f;
};

UCLASS()
class INVISIBLE_API UTraitActionResolver : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

public:
	// 写入并返回行为配置
	UFUNCTION(BlueprintCallable, Category="Trait|Action")
	static FTraitResolvedAction ResolveAction(
		const FTraitInteractionRule& Rule,
		const UTraitActionProfile* ActionProfile);
};
