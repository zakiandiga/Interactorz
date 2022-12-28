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
		//DataContainersToDisplay.Emplace(DataContainer);
		InventoryList->AddItem(DataContainer);
	}

	//OnDisplayingInventoryList();
}

void UInGameMenu::ClearInventoryList()
{
	InventoryList->ClearListItems();
}

void UInGameMenu::OnListViewClicked(UObject* ClickedObject)
{
	
	UInventoryDataEntryContainer* ItemToProcess = Cast<UInventoryDataEntryContainer>(ClickedObject);

	if (ItemToProcess == nullptr) return;

	FString ItemToPrint = ItemToProcess->InventoryDataContainer.Item->ItemData.Name;
	UE_LOG(LogTemp, Warning, TEXT("List clicked %s!"), *ItemToPrint);

	//drop the item
	// 
	//reduce the value by 1
	//remove from the list if 0
	//APickupItem PickupToSpawn = APickupItem(ItemToProcess->InventoryDataContainer.Item, 1);

	DropItem(ItemToProcess);
	int32 CurrentQuantity = ItemToProcess->InventoryDataContainer.ItemQuantity;
	CurrentQuantity -= 1;
	OwnerInventory->RemoveFromInventory(ItemToProcess->InventoryDataContainer.Item, 1);

	ClearInventoryList();
	DisplayInventoryList();

}

void UInGameMenu::DropItem(UInventoryDataEntryContainer* ItemToProcess)
{
	float RandomYaw = FMath::FRandRange(0.f, 360.f);
	FRotator SpawnRotation = OwnerInventory->GetOwner()->GetActorRotation();
	SpawnRotation.Yaw = RandomYaw;
	APickupItem* PickupToSpawn = GetWorld()->SpawnActor<APickupItem>(OwnerInventory->GetOwner()->GetActorLocation(), OwnerInventory->GetOwner()->GetActorRotation());
	PickupToSpawn->SpawnInit(ItemToProcess->InventoryDataContainer.Item, 1);
}



