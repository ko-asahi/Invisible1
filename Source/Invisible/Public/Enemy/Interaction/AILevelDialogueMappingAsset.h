// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AILevelDialogueMappingAsset.generated.h"



/**
 * 关卡文本库映射项，用于建立关卡与文本库的映射
 */

USTRUCT(BlueprintType)
struct FLevelDialogueTableMapping
{
	GENERATED_BODY()

	// 关卡名
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|Dialogue")
	FName LevelName = NAME_None;

	// 该关卡对应文本库
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|Dialogue")
	TSoftObjectPtr<UDataTable> DialogueTable = nullptr;
};

/**
 * 关卡文本库映射资产
 */

UCLASS(BlueprintType)
class INVISIBLE_API UAILevelDialogueMappingAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	// 默认文本库
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI|Dialogue")
	TSoftObjectPtr<UDataTable> DefaultDialogueTable = nullptr;

	// 关卡文本库映射表
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI|Dialogue")
	TArray<FLevelDialogueTableMapping> LevelMappings;

	// 根据关卡名获取文本库，若没有，则回退默认文本库（该方法抽自 AIBehaviorDialogueSubsystem）
	const UDataTable* ResolveTableByLevel(FName InLevelName) const;
};
