// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerState.h"
#include "InvisiblePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class INVISIBLE_API AInvisiblePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	// 添加一张钥匙卡；返回 true 表示本次确实新增了卡。
	UFUNCTION(BlueprintCallable, Category = "Inventory|KeyCards")
	bool AddKeyCard(FGameplayTag KeyCardTag);

	// 是否持有指定钥匙卡。无效 Tag 会返回 false。
	UFUNCTION(BlueprintPure, Category = "Inventory|KeyCards")
	bool HasKeyCard(FGameplayTag KeyCardTag) const;

	// 获取当前持有的所有钥匙卡。
	UFUNCTION(BlueprintPure, Category = "Inventory|KeyCards")
	const FGameplayTagContainer& GetOwnedKeyCards() const { return OwnedKeyCards; }

protected:
	// 玩家已拾取的钥匙卡集合，使用 GameplayTag 便于多个门共享同一套配置。
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Inventory|KeyCards", meta = (Categories = "KeyCard"))
	FGameplayTagContainer OwnedKeyCards;
};
