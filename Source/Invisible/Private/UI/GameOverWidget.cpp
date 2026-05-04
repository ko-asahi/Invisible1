// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameOverWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

// UMG控件初始化函数
void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UGameOverWidget::HandleRestartClicked);
	}
	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UGameOverWidget::HandleMainMenuClicked);
	}
}

// 重新开始按钮点击事件
void UGameOverWidget::HandleRestartClicked()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	const FName CurrentLevelName(*UGameplayStatics::GetCurrentLevelName(this, true));
	UGameplayStatics::OpenLevel(this, CurrentLevelName);
}

// 主菜单按钮点击事件
void UGameOverWidget::HandleMainMenuClicked()
{
	if (MainMenuLevelName.IsNone())
	{
		return;
	}
	UGameplayStatics::OpenLevel(this, MainMenuLevelName);
}