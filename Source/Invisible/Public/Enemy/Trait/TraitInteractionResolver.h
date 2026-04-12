// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Enemy/Trait/TraitDefinition.h"
#include "TraitInteractionResolver.generated.h"

/**
 * TraitInteractionResolver是一个特质互动计算器，用于获取特质定义，并计算最终权重
 */
class AEnemyBase;

// 用于记录最终计算结果的结构体
USTRUCT(BlueprintType)
struct FTraitInteractionDecision
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	bool bCanExecute = false;

	// UPROPERTY(BlueprintReadOnly)
	// float FinalScore = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag SuggestedBehaviorTag;

	UPROPERTY(BlueprintReadOnly)
	TArray<FText> MatchedTraitDescriptions;
};


UCLASS()
class INVISIBLE_API UTraitInteractionResolver : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:
	// 计算特质互动权重，返回最终决策结果
    UFUNCTION(BlueprintCallable, Category="Trait")
    static FTraitInteractionDecision EvaluateInteraction(
        UObject* WorldContextObject,
        AEnemyBase* SourceAI,
        AActor* TargetActor,
        ETraitInteractionType InteractionType);
	
};
