// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryDataEntryContainer.h"

/*
UInventoryDataEntryContainer::UInventoryDataEntryContainer()
{
	DataEntryContainer = FInventoryEntryDataContainer();
}
*/

FInventoryEntryDataContainer UInventoryDataEntryContainer::SetDataEntryContainer(UTexture2D* ItemIcon, FString ItemName, int32 ItemQuantity)
{	
	DataEntryContainer.ItemIcon = ItemIcon;
	DataEntryContainer.ItemName = ItemName;
	DataEntryContainer.ItemQuantity = ItemQuantity;
	return DataEntryContainer;
}
