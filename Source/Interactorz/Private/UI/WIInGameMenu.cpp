// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/WIInGameMenu.h"
#include "UI/InventoryListEntry.h"
#include "UI/InventoryEntryDataContainer.h"
#include "UI/WIWidgetSwitcher.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"
#include "Components/ListView.h"
#include "Inventory.h"
#include "DAItemData.h"
#include "Interactable/PickupItem.h"

void UWIInGameMenu::SetMainPanelVisible()
{
	MainPanel->SetVisibility(ESlateVisibility::Visible);
	PageSwitcher->OnPanelVisible(true);
}

void UWIInGameMenu::SetMainPanelHidden()
{
	MainPanel->SetVisibility(ESlateVisibility::Hidden);	
	PageSwitcher->OnPanelVisible(false);
}


