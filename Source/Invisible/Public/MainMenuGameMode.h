#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

class UUserWidget;

UCLASS()
class INVISIBLE_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
    // 初始化函数
	virtual void BeginPlay() override;

    // 构造函数
    AMainMenuGameMode();

	// 主菜单界面类
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="MainMenu")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	// 主菜单界面实例
	UPROPERTY()
	TObjectPtr<UUserWidget> MainMenuWidgetInstance = nullptr;
};