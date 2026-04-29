// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "Enemy/Enum/TraitCatalog.h"
#include "TraitSubsystem.generated.h"

/**
 * TraitSubsystem是一个自定义子系统，负责构建起 Tag 与 TraitDefinition 间的关系（关联Tag和行为配置）
 */
UCLASS()
class INVISIBLE_API UTraitSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	

public:
	// 载入特质配置文件
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Trait")
	TObjectPtr<UTraitCatalog> TraitCatalog = nullptr;

	// 初始化 Map ,不重复 Tag 地写入特质配置
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// 运行时设置特质目录并重建映射（建议在 BeginPlay 调用一次）
	UFUNCTION(BlueprintCallable, Category="Trait")
	void SetTraitCatalog(UTraitCatalog* InTraitCatalog);

	// 根据Tag查找特质定义
	UFUNCTION(BlueprintPure, Category="Trait")
	UTraitDefinition* FindTraitDefByTag(FGameplayTag TraitTag) const;

	// 根据Tags解析特质定义
	UFUNCTION(BlueprintPure, Category="Trait")
	void ResolveTraitDefs(const FGameplayTagContainer& TraitTags, TArray<UTraitDefinition*>& OutDefs) const;


private:
	// 重建特质映射
	void RebuildTraitMap();

	// 特质Map
	TMap<FGameplayTag, TObjectPtr<UTraitDefinition>> TraitMap;
};
