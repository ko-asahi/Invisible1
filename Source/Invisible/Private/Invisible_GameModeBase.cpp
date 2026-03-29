// Fill out your copyright notice in the Description page of Project Settings.


#include "Invisible_GameModeBase.h"

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
    Super::EndPlay(EndPlayReason);
}
