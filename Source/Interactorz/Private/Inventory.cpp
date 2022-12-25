#include "Inventory.h"
#include "DA_ItemData.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	//Does Inventory need Tick?
	PrimaryComponentTick.bCanEverTick = false;
	
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();
}

void UInventory::AddToInventory(UDA_ItemData* ItemToAdd, int32 QuantityToAdd)
{
	
	int32 newQuantity = CheckItemQuantityInInventory(ItemToAdd) + QuantityToAdd;

	ActiveInventory.Emplace(ItemToAdd, newQuantity);
}

void UInventory::RemoveFromInventory(UDA_ItemData* ItemToRemove, int32 QuantityToRemove)
{
	if(!CheckItemAvailable(ItemToRemove) || CheckItemQuantityInInventory(ItemToRemove) - QuantityToRemove < 0) return;

	int32 newQuantity = CheckItemQuantityInInventory(ItemToRemove) - QuantityToRemove;

	ActiveInventory.Emplace(ItemToRemove, newQuantity);

	if (CheckItemQuantityInInventory(ItemToRemove) <= 0)
	{
		ActiveInventory.FindAndRemoveChecked(ItemToRemove);
	}
}

bool UInventory::CheckItemAvailable(UDA_ItemData* ItemToCheck) const
{	
	return ActiveInventory.Contains(ItemToCheck);
}

int32 UInventory::CheckSpaceAvailable() const
{
	return InventoryLimit - ActiveInventory.Num();
}

int32 UInventory::CheckItemQuantityInInventory(UDA_ItemData* ItemToCheck) const
{
	return CheckItemAvailable(ItemToCheck) ? ActiveInventory.FindRef(ItemToCheck) : 0;
}


