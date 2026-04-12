// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Trait/TraitSubsystem.h"

// 初始化 Map ,不重复 Tag 地写入特质配置
void UTraitSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    RebuildTraitMap();
}

void UTraitSubsystem::SetTraitCatalog(UTraitCatalog* InTraitCatalog)
{
    TraitCatalog = InTraitCatalog;
    RebuildTraitMap();
}

void UTraitSubsystem::RebuildTraitMap()
{
    TraitMap.Empty();
    if(!TraitCatalog)
    {
        UE_LOG(LogTemp, Warning, TEXT("[TraitSubsystem] TraitCatalog is null, TraitMap build skipped."));
        return;
    }

    // 遍历每个特质地配置
    for(UTraitDefinition* TraitDef : TraitCatalog->TraitDefinitions)
    {
        // 跳过空配置或无效Tag
        if(!TraitDef || !TraitDef->TraitTag.IsValid()) continue;

        // 检查 Tag 是否已存在，若不存在则写入，存在则覆盖
        TraitMap.FindOrAdd(TraitDef->TraitTag) = TraitDef;
    }

    UE_LOG(LogTemp, Log, TEXT("[TraitSubsystem] TraitMap rebuilt, entries=%d"), TraitMap.Num());
}

// 根据Tag查找特质定义
UTraitDefinition* UTraitSubsystem::FindTraitDefByTag(FGameplayTag TraitTag) const
{
    if(const TObjectPtr<UTraitDefinition>* Found = TraitMap.Find(TraitTag))
    {
        return Found->Get();
    }
    return nullptr;
}


// 根据Tags解析特质定义
void UTraitSubsystem::ResolveTraitDefs(const FGameplayTagContainer& TraitTags, TArray<UTraitDefinition*>& OutDefs) const
{
    OutDefs.Reset();    // 重置输出数组，防止其中有上次残留数据

    // 遍历输入的 Tag 容器，将其中含有的 Tag 对应的特质配置写入输出数组中
    for(const FGameplayTag& Tag : TraitTags)
    {
        if(UTraitDefinition* Def = FindTraitDefByTag(Tag))
        {
            OutDefs.Add(Def);
        }
    }

    // 对输出数组进行排序，按照优先级从高到低排序
    OutDefs.Sort([](const UTraitDefinition& A, const UTraitDefinition& B)
    {
        return A.Priority > B.Priority; // 高优先级在前
    });
}

