// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "InvisibleGameStateBase.generated.h"

/**
 * 
 */

// 创建宏，用于广播对于ai听觉范围的修改
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGlobalHearingRangeChanged, float, NewRange);

UCLASS()
class INVISIBLE_API AInvisibleGameStateBase : public AGameStateBase
{
	GENERATED_BODY()


public:
	// 全局统一听觉范围
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Perception|Hearing",
		meta = (ClamMin = "0.0",UIMin = "0.0"))
	float GlobalHearingRange = 1500.0f;

	// BlueprintCallable，蓝图和代码都可调用修改
	UFUNCTION(BlueprintCallable, Category="AI|Perception|Hearing")
    void SetGlobalHearingRange(float NewRange);

	UFUNCTION(BlueprintPure, Category = "AI|Perception|Hearing")
	float GetGlobalHearingRange() const { return GlobalHearingRange; }

	// 广播对于ai听觉范围的修改
	UPROPERTY(BlueprintAssignable, Category = "AI|Perception|Hearing")
	FOnGlobalHearingRangeChanged OnGlobalHearingRangeChanged;
};
