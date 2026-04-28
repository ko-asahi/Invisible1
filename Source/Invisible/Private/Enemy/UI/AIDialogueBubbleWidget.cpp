// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/UI/AIDialogueBubbleWidget.h"

void UAIDialogueBubbleWidget::ShowDialogueText(const FText& InText)
{
    BP_OnShowDialogueText(InText);
}

void UAIDialogueBubbleWidget::ClearDialogueText()
{
    BP_OnClearDialogueText();
}
