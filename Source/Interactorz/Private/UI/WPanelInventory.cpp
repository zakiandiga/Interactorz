// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WPanelInventory.h"
#include "UI/InGameMenu.h"
#include "UI/InventoryListEntry.h"
#include "UI/InventoryDataEntryContainer.h"
#include "Components/PanelWidget.h"
#include "Components/ListView.h"
#include "DA_ItemData.h"
#include "Inventory.h"

void UWPanelInventory::NativeConstruct()
{
	Super::NativeConstruct();
	UInGameMenu* Parent = Cast<UInGameMenu>(GetParent()->GetOuter()->GetOuter());

	if (Parent == nullptr) return;

	Parent->OnMenuCreated.AddDynamic(this, &UWPanelInventory::AssignOwnerInventory);
}

void UWPanelInventory::AssignOwnerInventory(UInGameMenu* Root)
{
	OwnerInventory = Root->GetOwnerInventory();
}

bool UWPanelInventory::ShouldCycleTargetIndex(int32 TargetIndex)
{
	return TargetIndex < 0 || TargetIndex > InventoryList->GetNumItems() -1;
}

int32 UWPanelInventory::CycleNextIndex(int32 TargetIndex)
{
	if (TargetIndex < 0)
	{
		return InventoryList->GetNumItems() - 1;
	}

	return 0;
}

void UWPanelInventory::SelectCurrentItem(UObject* SelectedItem, bool IsSelected)
{
	if (!IsSelected) return;

	InventoryList->SetSelectedItem(SelectedItem);
	SetSelectedInventoryListIndex(InventoryList->GetIndexForItem(SelectedItem));
}

void UWPanelInventory::SelectionChange(float Value)
{
	int32 TargetIndex = SelectedInventoryListIndex + (int32)Value;

	if (ShouldCycleTargetIndex(TargetIndex))
	{
		TargetIndex = CycleNextIndex(TargetIndex);
	}

	SelectCurrentItem(InventoryList->GetItemAt(TargetIndex), true);
}


void UWPanelInventory::OnPageOpened_Implementation(UWidget* OpenedWidget)
{
	DisplayInventoryList();
}

void UWPanelInventory::OnPageClosed_Implementation(UWidget* ClosedWidget)
{
	ClearInventoryList();
}

void UWPanelInventory::OnListViewClicked(UObject* ClickedObject)
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

void UWPanelInventory::DisplayInventoryList()
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

	SetSelectedInventoryListIndex(GetSelectedInventoryListIndex());
	SelectionChange(0);


}

void UWPanelInventory::ClearInventoryList()
{
	if (OwnerInventory == nullptr) return;

	InventoryList->ClearListItems();
}




