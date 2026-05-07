// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */

class UButton;

UCLASS()
class INVISIBLE_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	// UMG控件初始化函数
	virtual void NativeConstruct() override;

	// 重新开始按钮
	UPROPERTY(meta=(BindWidget))
	UButton* RestartButton = nullptr;

	// 主菜单按钮
	UPROPERTY(meta=(BindWidget))
	UButton* MainMenuButton = nullptr;

	// 主菜单关卡名称
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameOver")
	FName MainMenuLevelName = TEXT("L_MainMenu");

	// 重新开始按钮点击事件
	UFUNCTION()
	void HandleRestartClicked();

	// 主菜单按钮点击事件
	UFUNCTION()
	void HandleMainMenuClicked();
	
};
