// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Trait/TraitActionProfile.h"

bool UTraitActionProfile::FindActionProfile(FGameplayTag BehaviorTag, FTraitActionProfileEntry& OutEntry) const
{
    if(!BehaviorTag.IsValid()) return false;

    for(const FTraitActionProfileEntry& Entry : ActionProfileEntries)
    {
        if(Entry.BehaviorTag == BehaviorTag)
        {
            OutEntry = Entry;
            return true;
        }
    }

    return false;
}

