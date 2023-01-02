// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/InGameMenu.h"
#include "UI/InventoryListEntry.h"
#include "UI/InventoryDataEntryContainer.h"
#include "UI/WIWidgetSwitcher.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"
#include "Components/ListView.h"
#include "Inventory.h"
#include "DA_ItemData.h"
#include "Interactable/PickupItem.h"

void UInGameMenu::SetMainPanelVisible()
{
	MainPanel->SetVisibility(ESlateVisibility::Visible);
	PageSwitcher->OnPanelVisible(true);
}

void UInGameMenu::SetMainPanelHidden()
{
	MainPanel->SetVisibility(ESlateVisibility::Hidden);	
	PageSwitcher->OnPanelVisible(false);
}