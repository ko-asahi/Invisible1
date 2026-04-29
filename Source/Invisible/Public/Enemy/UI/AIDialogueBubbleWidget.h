// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AIDialogueBubbleWidget.generated.h"

/**
 * UAIDialogueBubbleWidget：AI对话气泡，用于显示AI对话文本
 */

// 抽象类
UCLASS(Abstract, Blueprintable)
class INVISIBLE_API UAIDialogueBubbleWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 显示对话文本
	UFUNCTION(BlueprintCallable, Category = "AI|Dialogue")
	void ShowDialogueText(const FText& InText);

	// 清除对话文本
	UFUNCTION(BlueprintCallable, Category = "AI|Dialogue")
	void ClearDialogueText();

protected:
	// 蓝图中实现：将文本写入到文本框中（BlueprintImplementableEvent用于实现C++声明，蓝图实现）
	UFUNCTION(BlueprintImplementableEvent, Category = "AI|Dialogue")
	void BP_OnShowDialogueText(const FText& InText);

	// 蓝图中实现：清除文本框中的文本或隐藏
	UFUNCTION(BlueprintImplementableEvent, Category = "AI|Dialogue")
	void BP_OnClearDialogueText();
};
