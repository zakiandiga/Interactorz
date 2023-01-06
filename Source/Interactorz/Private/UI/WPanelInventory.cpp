// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WPanelInventory.h"
#include "UI/InGameMenu.h"
#include "UI/InventoryListEntry.h"
#include "UI/InventoryDataEntryContainer.h"
#include "Components/PanelWidget.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "DA_ItemData.h"
#include "Inventory.h"

void UWPanelInventory::NativeConstruct()
{
	Super::NativeConstruct();
	UInGameMenu* Parent = Cast<UInGameMenu>(GetParent()->GetOuter()->GetOuter());

	if (Parent == nullptr) return;

	Parent->OnMenuCreated.AddDynamic(this, &UWPanelInventory::AssignOwnerInventory);
	DescriptionText->SetText(FText());
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
	if (SelectedItem == nullptr) return;
	if (!IsSelected) return;

	InventoryList->SetSelectedItem(SelectedItem);
	InventoryList->SetSelectedIndex(InventoryList->GetIndexForItem(SelectedItem));
	SetSelectedItemIndex(InventoryList->GetIndexForItem(SelectedItem));
	SetDescriptionText(SelectedItem);
}

void UWPanelInventory::SelectionChange(float Value)
{
	int32 TargetIndex = SelectedItemIndex + (int32)Value;

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
	InventoryList->SetSelectedItem(nullptr);
	ClearInventoryList();
}

void UWPanelInventory::ProcessItem(UObject* ClickedObject, EItemProcessType ProcessType = EItemProcessType::EIP_Use)
{
	UInventoryDataEntryContainer* ItemToProcess = Cast<UInventoryDataEntryContainer>(ClickedObject);

	if (ItemToProcess == nullptr) return;

	int32 CurrentQuantity = ItemToProcess->GetItemData().ItemQuantity;
	CurrentQuantity -= 1;

	OwnerInventory->ProcessItem(ProcessType, ItemToProcess->GetItemData().Item, 1);

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

	InventoryList->GetItemAt(GetSelectedItemIndex()) == nullptr ?
		SelectCurrentItem(InventoryList->GetItemAt(0), true) :
		SelectCurrentItem(InventoryList->GetItemAt(GetSelectedItemIndex()), true);
}

void UWPanelInventory::ClearInventoryList()
{
	if (OwnerInventory == nullptr) return;

	InventoryList->ClearListItems();
	DescriptionText->SetText(FText());
}

FString UWPanelInventory::GetItemDescriptionText(UObject* ObjectToGet)
{
	UInventoryDataEntryContainer* DataContainer = Cast<UInventoryDataEntryContainer>(ObjectToGet);

	if (DataContainer == nullptr)
	{
		return FString("DESCRIPTION NOT FOUND!");
	}

	return DataContainer->GetItemData().Item->ItemData.Description;
}

void UWPanelInventory::SetDescriptionText(UObject* ObjectToSet)
{	
	if (ObjectToSet == nullptr) return;

	DescriptionText->SetText(FText::FromString(GetItemDescriptionText(ObjectToSet)));
}