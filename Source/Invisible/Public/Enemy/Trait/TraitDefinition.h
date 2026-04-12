// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "TraitDefinition.generated.h"

/**
 * UTraitDefinition是一个自定义数据资产，用于定义特质的行为参数以及相关UI文本
 */

UENUM(BlueprintType)
enum class ETraitInteractionType : uint8
{
	AI_With_AI	UMETA(DisplayName = "AI 与 AI"),
	AI_With_Object	UMETA(DisplayName = "AI 与 物体")
};



USTRUCT(BlueprintType)
struct FTraitInteractionRule
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETraitInteractionType InteractionType = ETraitInteractionType::AI_With_AI;

	// 目标标签过滤
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "Interaction.Target"))
	FGameplayTagContainer TargetTagsAny;

	// 执行倾向（大于0执行，小于0不执行）
	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// float ScoreDelta = 0.0f;

	// 成功执行概率倍率（暂留）
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin="0.0"))
	// float SuccessMultiplier = 1.0f;

	// 命中规则时推荐行为（由执行倾向和冲突规则共同决定），可理解为命中时触发的行为，只是增加了权重计算和冲突计算，权重计算已删除
	// 命中规则时推荐行为（兼容旧逻辑）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "Behavior.AI"))
	FGameplayTag SuggestedBehaviorTag;

	// 交互动作 Tag ，为空时回退到 SuggestedBehaviorTag
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "Behavior.AI"))
	FGameplayTag InteractionActionTag;

	// 交互动作按钮文本，为空时使用默认映射
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText InteractionActionButtonText;

	// 交互动作能量消耗，小于0时使用默认映射
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "-1.0"))
	float ActionEnergyCostOverride = -1.0f;

	// 交互动作执行距离（半径），小于0时使用默认映射
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "-1.0"))
	float ExecutionRadiusOverride = -1.0f;

	// 交互动作持续时间，小于0时使用默认映射
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "-1.0"))
	float DurationOverride = -1.0f;
	
	
};

UCLASS(BlueprintType)
class INVISIBLE_API UTraitDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

	
public:
	// 特质ID（唯一）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Trait.AI"))
	FGameplayTag TraitTag;
	
	// UI信息

	// 特质名称
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DisplayName;

	// 特质描述
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine = true))
	FText Description;

	// 冲突与优先级
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 Priority = 0;

	// 排斥特质
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Trait.AI"))
    FGameplayTagContainer ExclusiveWith;

    // 互动规则
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FTraitInteractionRule> Rules;
	
};
