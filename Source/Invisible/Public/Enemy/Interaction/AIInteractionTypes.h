#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Enemy/Trait/TraitDefinition.h"
#include "AIInteractionTypes.generated.h"

class AActor;
class AEnemyBase;

// 事件的结束原因
UENUM(BlueprintType)
enum class EInteractionEndReason : uint8	// 8位存储，支持最大256个选项
{
	Completed		UMETA(DisplayName = "正常完成"),
	Interrupted		UMETA(DisplayName = "中断"),
	InvalidTarget	UMETA(DisplayName = "目标失效")
};

// 两者共用变量规格，UI层与执行层共用
USTRUCT(BlueprintType)
struct FResolvedInteractionSpec
{
	GENERATED_BODY()

	// 行为Tag
	UPROPERTY(BlueprintReadOnly, Category = "EditMode|Interaction")
	FGameplayTag ActionTag;

	// 能量消耗
	UPROPERTY(BlueprintReadOnly, Category = "EditMode|Interaction")
	float EnergyCost = 0.0f;

	// 执行距离
	UPROPERTY(BlueprintReadOnly, Category = "EditMode|Interaction")
	float ExecutionRadius = 150.0f;

	// 行为持续时长
	UPROPERTY(BlueprintReadOnly, Category = "EditMode|Interaction")
	float Duration = 10.0f;

	bool IsValid() const
	{
		return ActionTag.IsValid() && EnergyCost >= 0.0f && ExecutionRadius >= 0.0f && Duration >= 0.0f;
	}
};


// 交互行为的配置内容，用于UI
USTRUCT(BlueprintType)
struct FInteractionActionOption
{
	GENERATED_BODY()

	// // 行为Tag
	// UPROPERTY(BlueprintReadOnly, Category = "EditMode|Interaction")
	// FGameplayTag ActionTag;

	// 按钮文本
	UPROPERTY(BlueprintReadOnly, Category = "EditMode|Interaction")
	FText ButtonText;

	// // 能量消耗
	// UPROPERTY(BlueprintReadOnly, Category = "EditMode|Interaction")
	// float EnergyCost = 0.0f;

	// // 执行距离
	// UPROPERTY(BlueprintReadOnly, Category = "EditMode|Interaction")
	// float ExecutionRadius = 150.0f;

	// // 行为持续时长
	// UPROPERTY(BlueprintReadOnly, Category = "EditMode|Interaction")
	// float Duration = 10.0f;

	// 交互规格
	UPROPERTY(BlueprintReadOnly, Category = "EditMode|Interaction")
	FResolvedInteractionSpec Spec;

};

// 运行时上下文，在点击后冻结（定死），其中的数据作为执行时的相关数据来源
USTRUCT(BlueprintType)
struct FTraitInteractionContext
{
	GENERATED_BODY()

	// 源ai
	UPROPERTY(BlueprintReadOnly, Category = "EditMode|Interaction")
	TObjectPtr<AActor> SourceActor = nullptr;

	// 目标
	UPROPERTY(BlueprintReadOnly, Category = "EditMode|Interaction")
	TObjectPtr<AActor> TargetActor = nullptr;

	// 交互对象类型
	UPROPERTY(BlueprintReadOnly, Category = "EditMode|Interaction")
	ETraitInteractionType InteractionType = ETraitInteractionType::AI_With_AI;

	// 交互规格
	UPROPERTY(BlueprintReadOnly, Category = "EditMode|Interaction")
	FResolvedInteractionSpec Spec;

	// 有效性判定
	bool IsValid() const
	{
		return SourceActor && TargetActor && Spec.IsValid();
	}

	// 获取交互行为的配置内容、交互双方以及交互类型，并写入运行时上下文
	static FTraitInteractionContext BuildFromOption(
		AActor* InSourceActor,
		AActor* InTargetActor,
		ETraitInteractionType InType,
		const FInteractionActionOption& InOption
	)
	{
		FTraitInteractionContext Out;
		Out.SourceActor = InSourceActor;
		Out.TargetActor = InTargetActor;
		Out.InteractionType = InType;
		Out.Spec = InOption.Spec;	// 将配置内容写入运行时上下文，此时可对原配置内容进行冻结，防止UI层修改带来不一致等影响
		return Out;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
    FOnAIInteractionActionClicked,
    FInteractionActionOption, ActionData,
    AEnemyBase*, SourceAI,
    AActor*, TargetAI
);