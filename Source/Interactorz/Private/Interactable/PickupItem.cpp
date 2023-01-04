// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/PickupItem.h"
#include "DA_ItemData.h"
#include "Inventory.h"
#include "Interfaces/InventoryOwner.h"

APickupItem::APickupItem()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemData = CreateDefaultSubobject<UDA_ItemData>(TEXT("Item Info"));
	ItemSprite = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Sprite"));
	
	SetRootComponent(ItemSprite);
	
	ItemSprite->SetStaticMesh(ItemData == nullptr ? nullptr : ItemData->ItemData.PickUpSprite);
	ItemSprite->SetSimulatePhysics(true);
	ItemSprite->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
}

bool APickupItem::CanInteract(const AActor* InteractingActor)
{
	return true;
}

void APickupItem::Interact(AActor* InteractingActor)
{	
	IInventoryOwner* InventoryOwner = Cast<IInventoryOwner>(InteractingActor);
	if (InventoryOwner == nullptr) return;

	UInventory* InteractingInventory = InventoryOwner->GetActorInventory();
	if (InteractingInventory == nullptr) return;
	
	if (InteractingInventory->CheckSpaceAvailable() < ItemQuantity)
	{
		UE_LOG(LogTemp, Warning, TEXT("Your inventory is full!"));
		InventoryOwner->OnItemTransferFailed();
		return;
	}

	InteractingInventory->ProcessItem(EItemProcessType::EIP_Retrieve, ItemData, ItemQuantity);
	UE_LOG(LogTemp, Warning, TEXT("%d of %s added to the %s"), ItemQuantity, *ItemData->ItemData.Name, *InteractingInventory->GetOwner()->GetActorNameOrLabel());
	InventoryOwner->OnItemTransferSuccess();
	Destroy();
}

void APickupItem::SpawnInitialize(UDA_ItemData* ItemDataToSet, int32 QuantityToSet)
{
	if (ItemDataToSet == nullptr) return;

	ItemData = ItemDataToSet;
	ItemSprite->SetStaticMesh(ItemDataToSet->ItemData.PickUpSprite);
	ItemQuantity = QuantityToSet;
}

FString APickupItem::GetInteractableName()
{
	return ItemData->ItemData.Name;
}


