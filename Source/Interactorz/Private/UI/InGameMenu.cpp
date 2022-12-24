// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameMenu.h"
#include "Components/CanvasPanel.h"

void UInGameMenu::SetMainPanelVisible()
{
	MainPanel->SetVisibility(ESlateVisibility::Visible);
}

void UInGameMenu::SetMainPanelHidden()
{
	MainPanel->SetVisibility(ESlateVisibility::Hidden);
}
