// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WIPanelInventory.h"
#include "UI/WIInGameMenu.h"
#include "UI/InventoryListEntry.h"
#include "UI/InventoryEntryDataContainer.h"
#include "Components/PanelWidget.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "DAItemData.h"
#include "Inventory.h"

void UWIPanelInventory::NativeConstruct()
{
	Super::NativeConstruct();
	UWIInGameMenu* Parent = Cast<UWIInGameMenu>(GetParent()->GetOuter()->GetOuter());

	if (Parent == nullptr) return;

	Parent->OnMenuCreated.AddDynamic(this, &UWIPanelInventory::AssignOwnerInventory);
	DescriptionText->SetText(FText());
}

void UWIPanelInventory::AssignOwnerInventory(UUserWidget* Root)
{
	OwnerInventory = Cast<UWIInGameMenu>(Root)->GetOwnerInventory();
}

bool UWIPanelInventory::ShouldCycleTargetIndex(int32 TargetIndex)
{
	return TargetIndex < 0 || TargetIndex > InventoryList->GetNumItems() -1;
}

int32 UWIPanelInventory::CycleNextIndex(int32 TargetIndex)
{
	if (TargetIndex < 0)
	{
		return InventoryList->GetNumItems() - 1;
	}

	return 0;
}

void UWIPanelInventory::SelectCurrentItem(UObject* SelectedItem, bool IsSelected)
{
	if (SelectedItem == nullptr) return;
	if (!IsSelected) return;

	InventoryList->SetSelectedItem(SelectedItem);
	InventoryList->SetSelectedIndex(InventoryList->GetIndexForItem(SelectedItem));
	SetSelectedItemIndex(InventoryList->GetIndexForItem(SelectedItem));
	SetDescriptionText(SelectedItem);
}

void UWIPanelInventory::SelectionChange(float Value)
{
	int32 TargetIndex = SelectedItemIndex + (int32)Value;

	if (ShouldCycleTargetIndex(TargetIndex))
	{
		TargetIndex = CycleNextIndex(TargetIndex);
	}

	SelectCurrentItem(InventoryList->GetItemAt(TargetIndex), true);
}

void UWIPanelInventory::OnPageOpened_Implementation(UWidget* OpenedWidget)
{
	DisplayInventoryList();
}

void UWIPanelInventory::OnPageClosed_Implementation(UWidget* ClosedWidget)
{
	InventoryList->SetSelectedItem(nullptr);
	ClearInventoryList();
}

void UWIPanelInventory::ProcessItem(UObject* ClickedObject, EItemProcessType ProcessType = EItemProcessType::EIP_Use)
{
	UInventoryEntryDataContainer* ItemToProcess = Cast<UInventoryEntryDataContainer>(ClickedObject);

	if (ItemToProcess == nullptr) return;

	int32 CurrentQuantity = ItemToProcess->GetDataContainer().ItemQuantity;
	CurrentQuantity -= 1;

	OwnerInventory->ProcessItem(ProcessType, ItemToProcess->GetDataContainer().Item, 1);

	ClearInventoryList();
	DisplayInventoryList();
}

void UWIPanelInventory::DisplayInventoryList()
{
	if (OwnerInventory == nullptr) return;

	for (TPair<UDAItemData*, int32>& item : OwnerInventory->GetActiveInventory())
	{
		if (item.Key == nullptr) return;

		UDAItemData* itemData = item.Key;
		UInventoryEntryDataContainer* DataContainer = NewObject<UInventoryEntryDataContainer>();
		DataContainer->SetDataContainer(itemData, item.Value);
		InventoryList->AddItem(DataContainer);		
	}

	InventoryList->GetItemAt(GetSelectedItemIndex()) == nullptr ?
		SelectCurrentItem(InventoryList->GetItemAt(0), true) :
		SelectCurrentItem(InventoryList->GetItemAt(GetSelectedItemIndex()), true);
}

void UWIPanelInventory::ClearInventoryList()
{
	if (OwnerInventory == nullptr) return;

	InventoryList->ClearListItems();
	DescriptionText->SetText(FText());
}

FString UWIPanelInventory::GetItemDescriptionText(UObject* ObjectToGet)
{
	UInventoryEntryDataContainer* DataContainer = Cast<UInventoryEntryDataContainer>(ObjectToGet);

	if (DataContainer == nullptr)
	{
		return FString("DESCRIPTION NOT FOUND!");
	}

	return DataContainer->GetDataContainer().Item->ItemData.Description;
}

void UWIPanelInventory::SetDescriptionText(UObject* ObjectToSet)
{	
	if (ObjectToSet == nullptr) return;

	DescriptionText->SetText(FText::FromString(GetItemDescriptionText(ObjectToSet)));
}