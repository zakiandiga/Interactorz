// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryListEntry.h"
#include "UI/InventoryDataEntryContainer.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Inventory.h"
#include "DA_ItemData.h"

void UInventoryListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UInventoryDataEntryContainer* Item = Cast<UInventoryDataEntryContainer>(ListItemObject);
	
	ItemIcon->SetBrushFromTexture(Item->GetDataEntryContainer().Item->ItemData.Icon, false);
	NameText->SetText(FText::FromString(Item->GetDataEntryContainer().Item->ItemData.Name));
	QuantityText->SetText(FText::FromString(FString::FromInt(Item->GetDataEntryContainer().ItemQuantity)));
}
