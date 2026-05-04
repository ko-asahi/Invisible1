// Fill out your copyright notice in the Description page of Project Settings.


#include "Invisible_GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Enemy/EnemyBase.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"
#include "InvisiblePlayerController.h"

AInvisible_GameModeBase::AInvisible_GameModeBase()
{
    DefaultPawnClass = APlayerCharacter::StaticClass();
}

void AInvisible_GameModeBase::BeginPlay()
{
    Super::BeginPlay();
}

void AInvisible_GameModeBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AInvisible_GameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(GameOverFallbackTimerHandle);
	}

    Super::EndPlay(EndPlayReason);
}

// 开始游戏结束
void AInvisible_GameModeBase::BeginGameOver(AEnemyBase* KillerEnemy)
{
    if(bGameOverStarted) return;

    

    bGameOverStarted = true;
    GameOverKillerEnemy = KillerEnemy;

    if (AInvisiblePlayerController* PC = Cast<AInvisiblePlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
    {
        PC->SetGameplayInputLocked(true);
    }

    if(UWorld* World = GetWorld())
    {
        const float Delay = FMath::Max(GameOverFallbackDelay, 0.0f);
        World->GetTimerManager().SetTimer(
            GameOverFallbackTimerHandle,
            this,
            &AInvisible_GameModeBase::FinishGameOverSequence,
            Delay,
            false
        );
    }
}

// 结束游戏结束
void AInvisible_GameModeBase::FinishGameOverSequence()
{
    if(!bGameOverStarted) return;

    if(UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(GameOverFallbackTimerHandle);
    }

    if(GameOverWidgetInstance)
    {
        return;
    }

    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if(!PC || !GameOverWidgetClass)
    {
        return;
    }

    GameOverWidgetInstance = CreateWidget<UUserWidget>(PC, GameOverWidgetClass);
    if(!GameOverWidgetInstance)
    {
        return;
    }

    // 添加结束界面
    GameOverWidgetInstance->AddToViewport(100);
    
    // 显示鼠标
    PC->bShowMouseCursor = true;

    // 设置为UI输入模式
    FInputModeUIOnly InputMode;
	PC->SetInputMode(InputMode);
}
