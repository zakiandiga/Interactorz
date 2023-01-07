// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryListEntry.h"
#include "UI/InventoryEntryDataContainer.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Inventory.h"
#include "DAItemData.h"

void UInventoryListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UInventoryEntryDataContainer* ItemDataContainer = Cast<UInventoryEntryDataContainer>(ListItemObject);
	
	Item = ItemDataContainer->GetDataContainer().Item;

	ItemIcon->SetBrushFromTexture(Item->ItemData.Icon, false);
	NameText->SetText(FText::FromString(Item->ItemData.Name));
	QuantityText->SetText(FText::FromString(FString::FromInt(ItemDataContainer->GetDataContainer().ItemQuantity)));
}
