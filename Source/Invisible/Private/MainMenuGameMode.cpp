#include "MainMenuGameMode.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

// 构造函数
AMainMenuGameMode::AMainMenuGameMode()
{
	DefaultPawnClass = nullptr;
}

// 初始化函数
void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	// 获取玩家控制器
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC || !MainMenuWidgetClass)
	{
		return;
	}

	// 创建主菜单界面实例
	MainMenuWidgetInstance = CreateWidget<UUserWidget>(PC, MainMenuWidgetClass);
	if (!MainMenuWidgetInstance)
	{
		return;
	}

	// 添加主菜单界面到视口
	MainMenuWidgetInstance->AddToViewport(100);

	// 显示鼠标
	PC->bShowMouseCursor = true;
    
	// 设置输入模式
	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(MainMenuWidgetInstance->TakeWidget());
	PC->SetInputMode(InputMode);
}