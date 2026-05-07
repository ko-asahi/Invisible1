// Fill out your copyright notice in the Description page of Project Settings.


#include "InvisiblePlayerState.h"

#include "Net/UnrealNetwork.h"

bool AInvisiblePlayerState::AddKeyCard(FGameplayTag KeyCardTag)
{
    if (!KeyCardTag.IsValid() || OwnedKeyCards.HasTagExact(KeyCardTag))
    {
        return false;
    }

    OwnedKeyCards.AddTag(KeyCardTag);
    return true;
}

bool AInvisiblePlayerState::HasKeyCard(FGameplayTag KeyCardTag) const
{
    return KeyCardTag.IsValid() && OwnedKeyCards.HasTagExact(KeyCardTag);
}

void AInvisiblePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AInvisiblePlayerState, OwnedKeyCards);
}