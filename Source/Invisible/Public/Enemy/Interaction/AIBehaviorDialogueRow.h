#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "AIBehaviorDialogueRow.generated.h"

/**
 * AI行为对话文本配置行：
 * 一行对应一个行为Tag，文本随机抽取
 */
USTRUCT(BlueprintType)
struct FAIBehaviorDialogueRow : public FTableRowBase
{
    GENERATED_BODY()

    // 行为Tag
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|Dialogue", meta = (Categories = "Behavior.AI"))
    FGameplayTag BehaviorTag;

    // 该行为对应的文本列表
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|Dialogue")
    TArray<FText> DialogueLines;

    // 该行是否有效（供C++读取时校验）
    bool IsValidRow() const
    {
        return BehaviorTag.IsValid() && DialogueLines.Num() > 0;
    }
};