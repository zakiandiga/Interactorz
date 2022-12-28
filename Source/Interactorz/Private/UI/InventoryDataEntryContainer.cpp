// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryDataEntryContainer.h"
#include "DA_ItemData.h"

void UInventoryDataEntryContainer::SetDataEntryContainer(UDA_ItemData* ItemData, int32 ItemQuantity)
{	
	InventoryDataContainer.Item = ItemData;
	InventoryDataContainer.ItemQuantity = ItemQuantity;
}
