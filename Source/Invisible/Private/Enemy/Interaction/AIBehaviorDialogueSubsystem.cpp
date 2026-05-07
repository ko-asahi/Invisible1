// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Interaction/AIBehaviorDialogueSubsystem.h"

#include "Engine/World.h"
#include "Misc/PackageName.h"
#include "Enemy/Interaction/AIBehaviorDialogueSettings.h"
#include "Enemy/Interaction/AIBehaviorDialogueRow.h"


// 获取关卡签名
FName UAIBehaviorDialogueSubsystem::GetNormalizedLevelName(const UWorld* World)
{
    if(!World) return NAME_None;

    // 获取关卡去除了包名的名称
    FString LevelName = FPackageName::GetShortName(World->GetMapName());

    // 处理获取到名称的 PIE 前缀
    if(LevelName.StartsWith(TEXT("UEDPIE_")))
    {
        TArray<FString> Parts;
        LevelName.ParseIntoArray(Parts, TEXT("_"), true);   // 将关卡名称按下划线分割

        // 重建短名中本身含有下划线“_”的关卡
        if(Parts.Num() >= 3 && Parts[0].Equals(TEXT("UEDPIE"), ESearchCase::IgnoreCase))
        {
            FString Rebuilt;
            for(int32 i = 2; i < Parts.Num(); i++)
            {
                if(!Rebuilt.IsEmpty())
                {
                    Rebuilt += TEXT("_");
                }
                Rebuilt += Parts[i];
            }
            LevelName = Rebuilt;
        }
    }
    return FName(*LevelName);
}


// 获取当前关卡的文本库
const UDataTable* UAIBehaviorDialogueSubsystem::ResolveDialogueTable(const UWorld* World) const
{
    // const FName CurrentLevel = GetNormalizedLevelName(World);

    // // 遍历映射表，查找当前关卡的文本库
    // for(const FLevelDialogueTableEntry& Entry : PerLevelDialogueTables)
    // {
    //     if(Entry.LevelName.IsNone() || !Entry.DialogueTable.IsValid() && Entry.DialogueTable.ToSoftObjectPath().IsNull() /*获取软指针 DialogueTable 指向的路径，并判断是否存在*/)
    //     {
    //         continue;
    //     }

    //     if(Entry.LevelName == CurrentLevel)
    //     {
    //         if(UDataTable* Table = Entry.DialogueTable.LoadSynchronous())
    //         {
    //             return Table;
    //         }
    //     }
    // }

    // // 回退默认库
    // if(UDataTable* Table = DefaultDialogueTable.LoadSynchronous())
    // {
    //     return Table;
    // }

    // // 返回空指针
    // return nullptr;
    const UAIBehaviorDialogueSettings* Settings = GetDefault<UAIBehaviorDialogueSettings>();
	if (!Settings)
	{
		return nullptr;
	}

    UAILevelDialogueMappingAsset* MappingAsset = Settings->LevelDialogueMappingAsset.LoadSynchronous();

	if (!MappingAsset)
	{
		return nullptr;
	}

	const FName CurrentLevel = GetNormalizedLevelName(World);
    
	return MappingAsset->ResolveTableByLevel(CurrentLevel);
}


// 在表中查找 Tag 完全匹配的行
const FAIBehaviorDialogueRow* UAIBehaviorDialogueSubsystem::FindRowByExactBehaviorTag(
    const UDataTable* Table,
    const FGameplayTag& BehaviorTag) const
{
    if(!Table || !BehaviorTag.IsValid())
    {
        return nullptr;
    }

    // 遍历 DataTable 所有行，精确匹配 Tag
    for(const TPair<FName, uint8*>& Pair : Table->GetRowMap())
    {
        const FAIBehaviorDialogueRow* Row = reinterpret_cast<const FAIBehaviorDialogueRow*>(Pair.Value);

        if(!Row)
        {
            continue;
        }

        if(Row->BehaviorTag.MatchesTagExact(BehaviorTag) && Row->IsValidRow())
        {
            return Row;
        }
    }

    return nullptr;
}

// 不重复抽取，抽取后再重置重抽
bool UAIBehaviorDialogueSubsystem::PickNonRepeatingLine(
    const FName& LevelName,
    const FGameplayTag& BehaviorTag,
    const TArray<FText>& Lines,
    FText& OutLine)
{
    OutLine = FText::GetEmpty();

    if(LevelName.IsNone() || !BehaviorTag.IsValid() || Lines.Num() <= 0)
    {
        return false;
    }

    FDialogueCycleKey Key;
    Key.LevelName = LevelName;
    Key.BehaviorTag = BehaviorTag;

    // 获取当前关卡该 Tag 对应的对话列表索引集合
    TSet<int32>& UsedSet = UsedLineIndicesCache.FindOrAdd(Key);

    // 若全部抽取过后，重置
    if(UsedSet.Num() >= Lines.Num())
    {
        UsedSet.Reset();
    }

    // 计算未抽取过的行索引
    TArray<int32> Candidates;
    Candidates.Reserve(Lines.Num());    // 初始化一个与 Lines 数组相同大小的数组

    for(int32 Index = 0; Index < Lines.Num(); Index++)
    {
        if(!UsedSet.Contains(Index))
        {
            Candidates.Add(Index);
        }
    }

    if(Candidates.Num() <= 0)
    {
        return false;
    }

    // 随机抽取一个未抽取过的行索引
    const int32 PickedIndex = Candidates[FMath::RandRange(0, Candidates.Num() - 1)];
    UsedSet.Add(PickedIndex);
    OutLine = Lines[PickedIndex];

    return true;
}

// 按行为 Tag 获取一条文本
bool UAIBehaviorDialogueSubsystem::TryGetDialogueLine(
    const UWorld* World,
    const FGameplayTag& BehaviorTag,
    FText& OutLine,
    FGameplayTag& OutMatchedBehaviorTag
)
{
    OutLine = FText::GetEmpty();
    OutMatchedBehaviorTag = FGameplayTag();

    if(!World || !BehaviorTag.IsValid())
    {
        return false;
    }

    const UDataTable* Table = ResolveDialogueTable(World);
	if (!Table)
	{
		return false;
	}

    const FName LevelName = GetNormalizedLevelName(World);
	if (LevelName.IsNone())
	{
		return false;
	}

    // 精确匹配
    const FAIBehaviorDialogueRow* Row = FindRowByExactBehaviorTag(Table, BehaviorTag);
	if (!Row)
	{
		return false;
	}

    OutMatchedBehaviorTag = BehaviorTag;

    return PickNonRepeatingLine(LevelName, BehaviorTag, Row->DialogueLines, OutLine);
}

// 自检功能
void UAIBehaviorDialogueSubsystem::DebugValidateDialogueForTag(
    const UWorld* World,
    const FGameplayTag& BehaviorTag,
    int32 SampleTimes
)
{
    if(!World || !BehaviorTag.IsValid() || SampleTimes <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("[DialogueDebug] 参数无效 World/BehaviorTag"));
        return;
    }

    const UDataTable* Table = ResolveDialogueTable(World);
    const FName LevelName = GetNormalizedLevelName(World);

    UE_LOG(LogTemp, Log, TEXT("[DialogueDebug] Level=%s Tag=%s Table=%s"), *LevelName.ToString(), *BehaviorTag.ToString(), *GetNameSafe(Table));

    if(!Table)
    {
        UE_LOG(LogTemp, Warning, TEXT("[DialogueDebug] 未找到文本库"));
        return;
    }

    const FAIBehaviorDialogueRow* Row = FindRowByExactBehaviorTag(Table, BehaviorTag);
    if(!Row)
    {
        UE_LOG(LogTemp, Warning, TEXT("[DialogueDebug] 未找到行为Tag对应的行:%s"), *BehaviorTag.ToString());
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("[DialogueDebug] 行文本数=%d"), Row->DialogueLines.Num());

    // 清空缓存，以便从初始状态开始多次重复抽取测试
    FDialogueCycleKey Key;
    Key.LevelName = LevelName;
    Key.BehaviorTag = BehaviorTag;
    UsedLineIndicesCache.Remove(Key);


    const int32 Times = FMath::Max(1, SampleTimes);
    for(int32 i = 0; i < Times; i++)
    {
        FText Line;
        FGameplayTag MatchedTag;
        const bool bSuccess = TryGetDialogueLine(World, BehaviorTag, Line, MatchedTag);
        UE_LOG(LogTemp, Log, TEXT("[DialogueDebug] 第%d次抽取:bSuccess=%s Line=%s MatchedTag=%s"), i + 1, bSuccess ? TEXT("true") : TEXT("false"), *Line.ToString(), *MatchedTag.ToString());
    }
}