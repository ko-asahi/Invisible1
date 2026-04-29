// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "Enemy/Interface/TraitTargetInterface.h"
#include "InteractableTargetBase.generated.h"

/**
 * 可互动物品基类（废弃，被接口方法替代）：
 * 提供目标Tag（供Trait规则过滤）
 * 负责显示/隐藏交互按钮
 * 将按钮点击转发为统一委托
 */

UCLASS()
class INVISIBLE_API AInteractableTargetBase : public AActor,public ITraitTargetInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableTargetBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

};
