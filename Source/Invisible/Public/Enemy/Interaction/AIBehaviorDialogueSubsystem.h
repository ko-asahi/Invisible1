// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "Enemy/Interaction/AILevelDialogueMappingAsset.h"
#include "AIBehaviorDialogueSubsystem.generated.h"

class UDataTable;
struct FAIBehaviorDialogueRow;

/**
 * 行为文本子系统：
 * 只负责读取映射资产并返回当前关卡应使用的文本库
 */

UCLASS(Config=Game, DefaultConfig)
class INVISIBLE_API UAIBehaviorDialogueSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	

public:
	// 指向关卡映射资产
	// UPROPERTY(EditAnywhere, Config, Category = "AI|Dialogue")
	// TSoftObjectPtr<UAILevelDialogueMappingAsset> LevelDialogueMappingAsset = nullptr;

	// 获取当前关卡的文本库，若没有，则退回默认文本库
	UFUNCTION(BlueprintCallable, Category = "AI|Dialogue")
	const UDataTable* ResolveDialogueTable(const UWorld* World) const;

	// 获取关卡签名
	UFUNCTION(BlueprintCallable, Category = "AI|Dialogue")
	static FName GetNormalizedLevelName(const UWorld* World);

	// 按行为 Tag 获取一条文本
	UFUNCTION(BlueprintCallable, Category = "AI|Dialogue")
	bool TryGetDialogueLine(
		const UWorld* World,
		const FGameplayTag& BehaviorTag,
		FText& OutLine,
		FGameplayTag& OutMatchedBehaviorTag
	);

	// 自检功能
	UFUNCTION(BlueprintCallable, Category = "AI|Dialogue|Debug")
	void DebugValidateDialogueForTag(
		const UWorld* World,
		const FGameplayTag& BehaviorTag,
		int32 SampleTimes = 10
	);

private:
	// 用于抽取去重的键
	struct FDialogueCycleKey
	{
		FName LevelName;
		FGameplayTag BehaviorTag;

		// 重载运算符，用于判断 Key 值是否已存在，用于去重
		bool operator==(const FDialogueCycleKey& Other) const
		{
			return LevelName == Other.LevelName && BehaviorTag == Other.BehaviorTag;
		}
	};

	// 生成 Key 对应的哈希值
	friend uint32 GetTypeHash(const FDialogueCycleKey& Key)
	{
		return HashCombine(GetTypeHash(Key.LevelName), GetTypeHash(Key.BehaviorTag));
	}

	// 通过 TMAP 缓存已被抽取过的行（Key：关卡名和行为Tag，Value：已被抽取过的行索引）
	TMap<FDialogueCycleKey, TSet<int32>> UsedLineIndicesCache;

	// 在表中查找 Tag 完全匹配的行
	const FAIBehaviorDialogueRow* FindRowByExactBehaviorTag(
		const UDataTable* Table,
		const FGameplayTag& BehaviorTag
	)const;

	// 不重复抽取，抽取后再重置重抽
	bool PickNonRepeatingLine(
		const FName& LevelName,
		const FGameplayTag& BehaviorTag,
		const TArray<FText>& Lines,
		FText& OutLine
	);
};
