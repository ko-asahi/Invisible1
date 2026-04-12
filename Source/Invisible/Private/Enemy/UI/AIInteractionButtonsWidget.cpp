// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/UI/AIInteractionButtonsWidget.h"
#include "Enemy/EnemyBase.h"

// 设置按钮数据
void UAIInteractionButtonsWidget::SetupAction(const TArray<FInteractionActionOption>& InAction, AEnemyBase* InSourceAI, AEnemyBase* InTargetAI)
{
    CachedActions = InAction;
    CachedSourceAI = InSourceAI;
    CachedTargetAI = InTargetAI;

    BP_RebuildButtons(CachedActions);
    BP_SetPanelVisible(CachedActions.Num() > 0);
}

// 按钮点击事件
void UAIInteractionButtonsWidget::NotifyActionClickedByIndex(int32 ActionIndex)
{
    if(!CachedActions.IsValidIndex(ActionIndex)) return;
    if(!CachedSourceAI.IsValid() || !CachedTargetAI.IsValid()) return;

    OnActionClicked.Broadcast(CachedActions[ActionIndex], CachedSourceAI.Get(), CachedTargetAI.Get());
}

// 清空按钮数据
void UAIInteractionButtonsWidget::ClearActions()
{
    CachedActions.Reset();
    CachedSourceAI.Reset();
    CachedTargetAI.Reset();

    BP_RebuildButtons(CachedActions);
    BP_SetPanelVisible(false);
}


