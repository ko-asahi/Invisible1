// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Player/PlayerCharacter.h"

#include "Invisible_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class INVISIBLE_API AInvisible_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	AInvisible_GameModeBase();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
};
