// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enemy/Interaction/AIInteractionTypes.h"
#include "AIInteractionButtonsWidget.generated.h"

/**
 * ai头顶会出现的按钮，用于选择交互行为
 */

class AEnemyBase;

UCLASS()
class INVISIBLE_API UAIInteractionButtonsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 创建委托对象
	UPROPERTY(BlueprintAssignable, Category = "AI|Interaction")
	FOnAIInteractionActionClicked OnActionClicked;
	
	// 设置按钮数据
	UFUNCTION(BlueprintCallable, Category = "AI|Interaction")
	void SetupAction(const TArray<FInteractionActionOption>& InAction, AEnemyBase* InSourceAI, AActor* InTargetAI);

	// 按钮点击事件
	UFUNCTION(BlueprintCallable, Category = "AI|Interaction")
	void NotifyActionClickedByIndex(int32 ActionIndex);

	// 根据数组动态生成按钮（推荐1-3个，最大支持5个）
	UFUNCTION(BlueprintImplementableEvent, Category="AI|Interaction")
    void BP_RebuildButtons(const TArray<FInteractionActionOption>& InActions);

	// 设置面板可见性
	UFUNCTION(BlueprintImplementableEvent, Category="AI|Interaction")
    void BP_SetPanelVisible(bool bVisible);

	// 清空按钮数据
	UFUNCTION(BlueprintCallable, Category="AI|Interaction")
    void ClearActions();

protected:
	// 缓存行为数据
	UPROPERTY(BlueprintReadOnly, Category="AI|Interaction")
	TArray<FInteractionActionOption> CachedActions;

	// 缓存源ai
	UPROPERTY(BlueprintReadOnly, Category="AI|Interaction")
	TWeakObjectPtr<AEnemyBase> CachedSourceAI;

	// 缓存目标ai
	UPROPERTY(BlueprintReadOnly, Category="AI|Interaction")
	TWeakObjectPtr<AActor> CachedTargetActor;
};
