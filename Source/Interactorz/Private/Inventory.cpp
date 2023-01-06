#include "Inventory.h"
#include "Interactable/PickupItem.h"
#include "DA_ItemData.h"

UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = false;	
}

void UInventory::UpdateInventorySpace()
{
	int32 CurrentTotalQuantity = 0;

	for (TPair<UDA_ItemData*, int32> InventoryEntry : ActiveInventory)
	{
		CurrentTotalQuantity += InventoryEntry.Value;
	}
	
	UsedInventorySpace = CurrentTotalQuantity;
}

void UInventory::AddToInventory(UDA_ItemData* ItemToAdd, int32 QuantityToAdd)
{	
	if (CheckSpaceAvailable() < QuantityToAdd)
	{
		UE_LOG(LogTemp, Warning, TEXT("INVENTORY IS FULL"));
		return;
	}

	int32 newQuantity = CheckItemQuantityInInventory(ItemToAdd) + QuantityToAdd;
	ActiveInventory.Emplace(ItemToAdd, newQuantity);
	UpdateInventorySpace();
}

void UInventory::RemoveFromInventory(UDA_ItemData* ItemToRemove, int32 QuantityToRemove)
{
	if(!CheckItemAvailable(ItemToRemove) || CheckItemQuantityInInventory(ItemToRemove) - QuantityToRemove < 0) return;

	int32 newQuantity = CheckItemQuantityInInventory(ItemToRemove) - QuantityToRemove;
	ActiveInventory.Emplace(ItemToRemove, newQuantity);

	if (CheckItemQuantityInInventory(ItemToRemove) > 0) return;
	
	ActiveInventory.FindAndRemoveChecked(ItemToRemove);	
	UpdateInventorySpace();
}

void UInventory::DropItem(UDA_ItemData* ItemToDrop, int32 QuantityToDrop)
{
	float RandomYaw = FMath::FRandRange(0.f, 360.f);
	FRotator SpawnRotation = GetOwner()->GetActorRotation();
	SpawnRotation.Yaw = RandomYaw;
	FVector SpawnLocation = GetOwner()->GetActorLocation() + DropLocationOffset;
	APickupItem* ItemToSpawn = GetWorld()->SpawnActor<APickupItem>(SpawnLocation, SpawnRotation);

	ItemToSpawn->SpawnInitialize(ItemToDrop, QuantityToDrop);
	RemoveFromInventory(ItemToDrop, QuantityToDrop);
}

void UInventory::UseItem()
{
	//to be implemented
}

void UInventory::ProcessItem(EItemProcessType ProcessType, UDA_ItemData* ItemToProcess, int32 QuantityToProcess)
{
	switch (ProcessType)
	{
	case EItemProcessType::EIP_Drop:
		DropItem(ItemToProcess, QuantityToProcess);
		break;
	case EItemProcessType::EIP_Use:
		UseItem();
		break;
	case EItemProcessType::EIP_Remove:
		RemoveFromInventory(ItemToProcess, QuantityToProcess);
		break;
	case EItemProcessType::EIP_Retrieve:
		AddToInventory(ItemToProcess, QuantityToProcess);
		break;
	default:
		break;
	}

}

bool UInventory::CheckItemAvailable(UDA_ItemData* ItemToCheck) const
{	
	return ActiveInventory.Contains(ItemToCheck);
}

int32 UInventory::CheckSpaceAvailable() const
{
	return MaxInventorySpace - UsedInventorySpace;
}

int32 UInventory::CheckItemQuantityInInventory(UDA_ItemData* ItemToCheck) const
{
	return CheckItemAvailable(ItemToCheck) ? ActiveInventory.FindRef(ItemToCheck) : 0;
}