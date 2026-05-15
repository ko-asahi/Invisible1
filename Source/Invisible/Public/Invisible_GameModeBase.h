// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Player/PlayerCharacter.h"

#include "Invisible_GameModeBase.generated.h"

/**
 * 
 */

class AEnemyBase;
class UUserWidget;

UCLASS()
class INVISIBLE_API AInvisible_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

public:

public:
	AInvisible_GameModeBase();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// 开始游戏结束
	UFUNCTION(BlueprintCallable, Category="GameOver")
	void BeginGameOver(AEnemyBase* KillerEnemy);

	// 使用指定延迟开始游戏结束（适用于没有结束动画的触发源，例如监控摄像头）
	UFUNCTION(BlueprintCallable, Category="GameOver")
	void BeginGameOverWithDelay(AEnemyBase* KillerEnemy, float FinishDelay);

	// 结束游戏结束
	UFUNCTION(BlueprintCallable, Category="GameOver")
	void FinishGameOverSequence();

	// 获取游戏结束序列是否已经开始
	UFUNCTION(BlueprintPure, Category="GameOver")
	bool IsGameOverStarted() const { return bGameOverStarted; }

protected:
	// 游戏结束界面类
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameOver")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	// 游戏结束界面延迟时间
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameOver")
	float GameOverFallbackDelay = 2.0f;

	// 游戏结束序列是否已经开始
	UPROPERTY(BlueprintReadOnly, Category="GameOver")
	bool bGameOverStarted = false;

	// 游戏结束界面实例
	UPROPERTY()
	TObjectPtr<UUserWidget> GameOverWidgetInstance = nullptr;

	// 游戏结束敌人
	UPROPERTY()
	TObjectPtr<AEnemyBase> GameOverKillerEnemy = nullptr;

	// 游戏结束计时器
	FTimerHandle GameOverFallbackTimerHandle;
	
};
