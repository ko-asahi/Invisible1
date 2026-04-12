#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Enemy/Trait/TraitDefinition.h"
#include "AIInteractionTypes.generated.h"

class AEnemyBase;


// 交互行为的配置内容
USTRUCT(BlueprintType)
struct FInteractionActionOption
{
	GENERATED_BODY()

	// 行为Tag
	UPROPERTY(BlueprintReadOnly, Category = "EditMode|Interaction")
	FGameplayTag ActionTag;

	// 按钮文本
	UPROPERTY(BlueprintReadOnly, Category = "EditMode|Interaction")
	FText ButtonText;

	// 能量消耗
	UPROPERTY(BlueprintReadOnly, Category = "EditMode|Interaction")
	float EnergyCost = 0.0f;

	// 执行距离
	UPROPERTY(BlueprintReadOnly, Category = "EditMode|Interaction")
	float ExecutionRadius = 150.0f;

	// 行为持续时长
	UPROPERTY(BlueprintReadOnly, Category = "EditMode|Interaction")
	float Duration = 10.0f;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
    FOnAIInteractionActionClicked,
    FInteractionActionOption, ActionData,
    AEnemyBase*, SourceAI,
    AEnemyBase*, TargetAI
);