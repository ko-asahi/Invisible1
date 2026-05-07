// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */

class UButton;

UCLASS()
class INVISIBLE_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	// UMG控件初始化函数
	virtual void NativeConstruct() override;

	// 退出游戏按钮
	UPROPERTY(meta=(BindWidget))
	UButton* ExitGameButton = nullptr;

	// 退出游戏按钮点击事件
	UFUNCTION()
	void HandleExitGameClicked();
};
