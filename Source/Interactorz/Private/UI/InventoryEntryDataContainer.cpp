// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryEntryDataContainer.h"
#include "DAItemData.h"

void UInventoryEntryDataContainer::SetDataContainer(UDAItemData* ItemData, int32 ItemQuantity)
{	
	InventoryDataContainer.Item = ItemData;
	InventoryDataContainer.ItemQuantity = ItemQuantity;
}
