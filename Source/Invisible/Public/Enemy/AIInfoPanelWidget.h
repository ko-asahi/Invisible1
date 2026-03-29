// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enemy/EnemyBase.h"
#include "AIInfoPanelWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVISIBLE_API UAIInfoPanelWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 更新敌人信息
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateAIInfo(const FAIInfoData& AIInfoData, AEnemyBase* InEnemy);
	
};
