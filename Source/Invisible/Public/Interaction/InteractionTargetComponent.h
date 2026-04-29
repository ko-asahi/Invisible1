// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Enemy/Interaction/AIInteractionTypes.h"
#include "InteractionTargetComponent.generated.h"

/**
 * 可互动物品组件：
 * 提供目标Tag（供Trait规则过滤）
 * 负责显示/隐藏交互按钮
 * 将按钮点击转发为统一委托
 * 
 * 可通过挂载到目标 Actor 来对其赋予交互属性
 */

class UWidgetComponent;
class UAIInteractionButtonsWidget;
class AEnemyBase;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVISIBLE_API UInteractionTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionTargetComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 是否启用交互
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bInteractionEnabled = true;

	// 目标Tag
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (Categories = "Interaction.Target"))
	FGameplayTagContainer InteractionTargetTags;

	// 按键组件类
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Interaction")
	TSubclassOf<UAIInteractionButtonsWidget> InteractionButtonsWidgetClass;

	// 按键组件的相对坐标
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Interaction")
	FVector WidgetLocalOffset = FVector(0.0f, 0.0f, 100.0f);

	// 点击选择的交互行为
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnAIInteractionActionClicked OnInteractionActionChosen;

	// 获取目标的Tag
	UFUNCTION(BlueprintPure, Category = "Interaction")
	const FGameplayTagContainer& GetInteractionTargetTags() const { return InteractionTargetTags; }

	// 显示交互按钮
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void ShowInteractionButtons(const TArray<FInteractionActionOption>& InActions, AEnemyBase* InSourceAI);

	// 隐藏交互按钮
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void HideInteractionButtons();

private:
	// 运行时按键组件
	UPROPERTY()
	TObjectPtr<UWidgetComponent> RuntimeWidgetComp = nullptr;

	// 按键点击句柄
	UFUNCTION()
	void HandleActionClicked(FInteractionActionOption ActionData, AEnemyBase* SourceAI, AActor* TargetActor);
};
