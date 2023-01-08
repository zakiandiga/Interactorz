#include "Inventory.h"
#include "Interactable/PickupItem.h"
#include "DAItemData.h"
#include "ItemAction.h"
#include "DebugHelpers/DebugMacros.h"

UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = false;	
}

void UInventory::UpdateInventorySpace()
{
	int32 CurrentTotalQuantity = 0;

	for (TPair<UDAItemData*, int32> InventoryEntry : ActiveInventory)
	{
		CurrentTotalQuantity += InventoryEntry.Value;
	}
	
	UsedInventorySpace = CurrentTotalQuantity;
}

void UInventory::AddToInventory(UDAItemData* ItemToAdd, int32 QuantityToAdd)
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

void UInventory::RemoveFromInventory(UDAItemData* ItemToRemove, int32 QuantityToRemove)
{
	if(!CheckItemAvailable(ItemToRemove) || CheckItemQuantityInInventory(ItemToRemove) - QuantityToRemove < 0) return;

	int32 newQuantity = CheckItemQuantityInInventory(ItemToRemove) - QuantityToRemove;
	ActiveInventory.Emplace(ItemToRemove, newQuantity);

	if (CheckItemQuantityInInventory(ItemToRemove) > 0) return;
	
	ActiveInventory.FindAndRemoveChecked(ItemToRemove);	
	UpdateInventorySpace();
}

void UInventory::DropItem(UDAItemData* ItemToDrop, int32 QuantityToDrop)
{
	float RandomYaw = FMath::FRandRange(0.f, 360.f);
	FRotator SpawnRotation = GetOwner()->GetActorRotation();
	SpawnRotation.Yaw = RandomYaw;
	FVector SpawnLocation = GetOwner()->GetActorLocation() + DropLocationOffset;
	APickupItem* ItemToSpawn = GetWorld()->SpawnActor<APickupItem>(SpawnLocation, SpawnRotation);

	ItemToSpawn->SpawnInitialize(ItemToDrop, QuantityToDrop);
	RemoveFromInventory(ItemToDrop, QuantityToDrop);
}

void UInventory::UseItem(UDAItemData* ItemToUse, int32 QuantityToUse)
{	
	UItemAction* ItemAction = ItemToUse->ItemAction.GetDefaultObject();

	if (ItemAction == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have ItemAction on its ItemData"), *ItemToUse->ItemData.Name);
		return;
	}

	ItemAction->UseItem(ItemToUse, GetOwner());
	RemoveFromInventory(ItemToUse, QuantityToUse);	
}

void UInventory::ProcessItem(EItemProcessType ProcessType, UDAItemData* ItemToProcess, int32 QuantityToProcess)
{
	switch (ProcessType)
	{
	case EItemProcessType::EIP_Drop:
		DropItem(ItemToProcess, QuantityToProcess);
		break;
	case EItemProcessType::EIP_Use:
		UseItem(ItemToProcess, QuantityToProcess);
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

bool UInventory::CheckItemAvailable(UDAItemData* ItemToCheck) const
{	
	return ActiveInventory.Contains(ItemToCheck);
}

int32 UInventory::CheckSpaceAvailable() const
{
	return MaxInventorySpace - UsedInventorySpace;
}

int32 UInventory::CheckItemQuantityInInventory(UDAItemData* ItemToCheck) const
{
	return CheckItemAvailable(ItemToCheck) ? ActiveInventory.FindRef(ItemToCheck) : 0;
}