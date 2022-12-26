// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/InGameMenu.h"
#include "UI/InventoryListEntry.h"
#include "UI/InventoryDataEntryContainer.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"
//#include "Components/ListView.h"
#include "Inventory.h"
#include "DA_ItemData.h"

void UInGameMenu::SetMainPanelVisible()
{
	MainPanel->SetVisibility(ESlateVisibility::Visible);
}

void UInGameMenu::SetMainPanelHidden()
{
	MainPanel->SetVisibility(ESlateVisibility::Hidden);	
	
}

void UInGameMenu::DisplayInventoryList()
{
	if (OwnerInventory == nullptr) return;
	for (TPair<UDA_ItemData*, int32>& item : OwnerInventory->GetActiveInventory())
	{
		if (item.Key == nullptr) return;

		UDA_ItemData* itemData = item.Key;
		UInventoryDataEntryContainer* DataContainer = NewObject<UInventoryDataEntryContainer>();
		DataContainer->SetDataEntryContainer(itemData->ItemInfo.Icon, itemData->ItemInfo.Name, item.Value);
		DataContainersToDisplay.Emplace(DataContainer);
	}

	OnDisplayingInventoryList(DataContainersToDisplay);
}


