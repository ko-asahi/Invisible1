#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "AIBehaviorDialogueSettings.generated.h"

class UAILevelDialogueMappingAsset;

/**
 * AI 行为对话系统全局设置（显示在 Project Settings）
 */
UCLASS(Config=Game, DefaultConfig, meta = (DisplayName = "AI Behavior Dialogue Settings"))
class INVISIBLE_API UAIBehaviorDialogueSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    // 指向关卡文本库映射资产
    UPROPERTY(EditAnywhere, Config, BlueprintReadOnly, Category = "AI|Dialogue")
    TSoftObjectPtr<UAILevelDialogueMappingAsset> LevelDialogueMappingAsset = nullptr;

// 预编译指令，在打包时不参与编译
#if WITH_EDITOR
    virtual FName GetCategoryName() const override
    {
        return FName(TEXT("Game"));
    }

    virtual FName GetSectionName() const override
    {
        return FName(TEXT("AI Behavior Dialogue"));
    }
#endif
};