// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/PlayerController.h"

// UMG控件初始化函数
void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (ExitGameButton)
	{
		ExitGameButton->OnClicked.RemoveDynamic(this, &UMainMenuWidget::HandleExitGameClicked);
		ExitGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::HandleExitGameClicked);
	}
}

// 退出游戏按钮点击事件
void UMainMenuWidget::HandleExitGameClicked()
{
	APlayerController* PC = GetOwningPlayer();
	UKismetSystemLibrary::QuitGame(
		this,
		PC,
		EQuitPreference::Quit,
		false
	);
}