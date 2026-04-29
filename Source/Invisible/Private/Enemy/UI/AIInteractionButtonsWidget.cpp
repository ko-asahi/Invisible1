// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/UI/AIInteractionButtonsWidget.h"
#include "Enemy/EnemyBase.h"

// 设置按钮数据
void UAIInteractionButtonsWidget::SetupAction(const TArray<FInteractionActionOption>& InAction, AEnemyBase* InSourceAI, AActor* InTargetActor)
{
    CachedActions = InAction;
    CachedSourceAI = InSourceAI;
    CachedTargetActor = InTargetActor;

    BP_RebuildButtons(CachedActions);
    BP_SetPanelVisible(CachedActions.Num() > 0);
}

// 按钮点击事件
void UAIInteractionButtonsWidget::NotifyActionClickedByIndex(int32 ActionIndex)
{
    if(!CachedActions.IsValidIndex(ActionIndex)) return;
    if(!CachedSourceAI.IsValid() || !CachedTargetActor.IsValid()) return;

    OnActionClicked.Broadcast(CachedActions[ActionIndex], CachedSourceAI.Get(), CachedTargetActor.Get());
}

// 清空按钮数据
void UAIInteractionButtonsWidget::ClearActions()
{
    CachedActions.Reset();
    CachedSourceAI.Reset();
    CachedTargetActor.Reset();

    BP_RebuildButtons(CachedActions);
    BP_SetPanelVisible(false);
}


