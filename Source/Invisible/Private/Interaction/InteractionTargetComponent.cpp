// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractionTargetComponent.h"
#include "Components/WidgetComponent.h"
#include "Enemy/UI/AIInteractionButtonsWidget.h"
#include "Enemy/EnemyBase.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UInteractionTargetComponent::UInteractionTargetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractionTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if(!Owner) return;

	// 获取运行时按键组件
	RuntimeWidgetComp = NewObject<UWidgetComponent>(Owner, TEXT("InteractionButtonsWidgetComp"));
	if(!RuntimeWidgetComp) return;
	
	RuntimeWidgetComp->SetupAttachment(Owner->GetRootComponent());
	RuntimeWidgetComp->SetRelativeLocation(WidgetLocalOffset);
	RuntimeWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	RuntimeWidgetComp->SetDrawAtDesiredSize(false);
	RuntimeWidgetComp->SetDrawSize(FVector2D(500.f, 120.f));
	RuntimeWidgetComp->SetPivot(FVector2D(0.5f, 0.0f));
	RuntimeWidgetComp->SetVisibility(false);

	// 将按键组件设置为运行时组件
	if(InteractionButtonsWidgetClass)
	{
		RuntimeWidgetComp->SetWidgetClass(InteractionButtonsWidgetClass);
	}
	RuntimeWidgetComp->RegisterComponent();
}


// Called every frame
void UInteractionTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// 按键显示
void UInteractionTargetComponent::ShowInteractionButtons(const TArray<FInteractionActionOption>& InActions, AEnemyBase* InSourceAI)
{
	if(!RuntimeWidgetComp || !bInteractionEnabled || !InSourceAI) return;

	UAIInteractionButtonsWidget* Widget = Cast<UAIInteractionButtonsWidget>(RuntimeWidgetComp->GetUserWidgetObject());
	if(!Widget)
	{
		RuntimeWidgetComp->InitWidget();
		Widget = Cast<UAIInteractionButtonsWidget>(RuntimeWidgetComp->GetUserWidgetObject());
	}
	if(!Widget) return;

	if(!Widget->OnActionClicked.IsAlreadyBound(this, &UInteractionTargetComponent::HandleActionClicked))
	{
		Widget->OnActionClicked.AddDynamic(this, &UInteractionTargetComponent::HandleActionClicked);
	}

	Widget->SetupAction(InActions, InSourceAI, GetOwner());
	RuntimeWidgetComp->SetVisibility(InActions.Num() > 0, true);
}

// 按键隐藏
void UInteractionTargetComponent::HideInteractionButtons()
{
	if(!RuntimeWidgetComp) return;

	if(UAIInteractionButtonsWidget* Widget = Cast<UAIInteractionButtonsWidget>(RuntimeWidgetComp->GetUserWidgetObject()))
	{
		Widget->ClearActions();
	}
	RuntimeWidgetComp->SetVisibility(false, true);
}

// 按键点击句柄
void UInteractionTargetComponent::HandleActionClicked(FInteractionActionOption ActionData, AEnemyBase* SourceAI, AActor* TargetActor)
{
	// 广播选择事件
	OnInteractionActionChosen.Broadcast(ActionData, SourceAI, TargetActor);
}

