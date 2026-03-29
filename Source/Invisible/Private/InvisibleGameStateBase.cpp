// Fill out your copyright notice in the Description page of Project Settings.


#include "InvisibleGameStateBase.h"

void AInvisibleGameStateBase::SetGlobalHearingRange(float NewRange)
{
    const float Clamped = FMath::Max(0.0f, NewRange);   // 确保范围不小于0
    // 如果范围没有变化，则不进行广播
    if(FMath::IsNearlyEqual(Clamped, GlobalHearingRange))
    {
        return;
    }

    GlobalHearingRange = Clamped;
    OnGlobalHearingRangeChanged.Broadcast(GlobalHearingRange);
}

