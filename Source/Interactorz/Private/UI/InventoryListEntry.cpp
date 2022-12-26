// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryListEntry.h"
#include "UI/InventoryDataEntryContainer.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Inventory.h"

void UInventoryListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UInventoryDataEntryContainer* Item = Cast<UInventoryDataEntryContainer>(ListItemObject);
	
	ItemIcon->SetBrushFromTexture(Item->DataEntryContainer.ItemIcon, false);
	NameText->SetText(FText::FromString(Item->DataEntryContainer.ItemName));
	QuantityText->SetText(FText::FromString(FString::FromInt(Item->DataEntryContainer.ItemQuantity)));	
}
