// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/InGameMenu.h"
#include "UI/InventoryListEntry.h"
#include "UI/InventoryDataEntryContainer.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"
#include "Components/ListView.h"
#include "Inventory.h"
#include "DA_ItemData.h"
#include "Interactable/PickupItem.h"

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
		DataContainer->SetDataEntryContainer(itemData, item.Value);
		InventoryList->AddItem(DataContainer);
	}
}

void UInGameMenu::ClearInventoryList()
{
	InventoryList->ClearListItems();
}

void UInGameMenu::OnListViewClicked(UObject* ClickedObject)
{	
	UInventoryDataEntryContainer* ItemToProcess = Cast<UInventoryDataEntryContainer>(ClickedObject);

	if (ItemToProcess == nullptr) return;

	int32 CurrentQuantity = ItemToProcess->GetItemData().ItemQuantity;
	CurrentQuantity -= 1;

	//Drop item for now, should be called from a command button groups that appear when the entry clicked
	OwnerInventory->ProcessItem(EItemProcessType::EIP_Drop, ItemToProcess->GetItemData().Item, 1);

	ClearInventoryList();
	DisplayInventoryList();
}




