// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/StorageActor.h"
#include "Inventory.h"
#include "UI/InGameHUD.h"


AStorageActor::AStorageActor()
{
	PrimaryActorTick.bCanEverTick = true;

	StorageMesh = CreateDefaultSubobject<UStaticMeshComponent>("Storage Mesh");
	StorageInventory = CreateDefaultSubobject<UInventory>("Storage Inventory");

}

void AStorageActor::BeginPlay()
{
	Super::BeginPlay();

	InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());	
}

void AStorageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AStorageActor::CanInteract(const AActor* InteractingActor)
{
	return false;
}

void AStorageActor::Interact(AActor* InteractingActor)
{
	//1. empty ? open interactor inventory : open this inventory 
	//2. the rest of the item transfer is being controlled from the UI until the UI closed
	//3. on finish interact:
	//CurrentInteractingInventoryOwner->OnItemTransferSuccess();
	//dont forget to null the CurrentInteractingInventoryOwner

	//Testing transfer item
	CurrentInteractingInventoryOwner = Cast<IInventoryOwner>(InteractingActor);
	if (CurrentInteractingInventoryOwner == nullptr)
	{
		//finish interaction right away, error, not a storage type
		return;
	}
	
	if (InGameHUD == nullptr) return;
	
	InGameHUD->OpenStorageMenu(true);
	//bind to on storage menu closed
	// on closed, ending interaction, back to player
	//TransferToInteractor(DEBUGITEMTOGIVE, DEBUGITEMQUANTITY);
}

void AStorageActor::TransferToInteractor(UDAItemData* ItemToGive, int32 QuantityToGive)
{
	UInventory* InteractingInventory = CurrentInteractingInventoryOwner->GetInventory();
	if (InteractingInventory == nullptr) return;

	if (InteractingInventory->CheckSpaceAvailable() < QuantityToGive)
	{
		// set error message to display "Your inventory is full!"
		return;
	}

	InteractingInventory->ProcessItem(EItemProcessType::EIP_Retrieve, ItemToGive, 5);
	StorageInventory->ProcessItem(EItemProcessType::EIP_Remove, ItemToGive, 5);
}

void AStorageActor::TransferFromInteractor(UDAItemData* ItemToGet, int32 QuantityToGet)
{
	UInventory* InteractingInventory = CurrentInteractingInventoryOwner->GetInventory();
	if (InteractingInventory == nullptr) return;

	if (StorageInventory->CheckSpaceAvailable() < QuantityToGet)
	{
		// set error message to display "Box can't hold more items!!"
		return;
	}

	StorageInventory->ProcessItem(EItemProcessType::EIP_Retrieve, ItemToGet, 5);
	InteractingInventory->ProcessItem(EItemProcessType::EIP_Remove, ItemToGet, 5);
}

FString AStorageActor::GetInteractableName()
{
	return FString::Printf(TEXT("TREASURE CHEST DEBUG TEST"));
}

void AStorageActor::OnItemTransferSuccess()
{
	//update inventory
	//display messages
}

void AStorageActor::OnItemTransferFailed()
{
	//update inventory
	//display messages
}

