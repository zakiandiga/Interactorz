// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/PickupItem.h"
#include "Components/SphereComponent.h"
#include "DA_ItemData.h"
#include "Inventory.h"
#include "Interfaces/InventoryOwner.h"

APickupItem::APickupItem()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemSprite = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Sprite"));
	ItemData = CreateDefaultSubobject<UDA_ItemData>(TEXT("Item Info"));
	
	SetRootComponent(ItemSprite);
	
	ItemSprite->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
}

bool APickupItem::CanInteract(const AActor* InteractingActor)
{
	return true; // InteractingActor == GetCurrentInteractableActor();
}

void APickupItem::Interact(AActor* InteractingActor)
{	
	IInventoryOwner* InventoryOwner = Cast<IInventoryOwner>(InteractingActor);
	UInventory* InteractingInventory = InventoryOwner->GetActorInventory();
	if (InteractingInventory == nullptr) return;
	
	if (InteractingInventory->CheckSpaceAvailable() < ItemQuantity)
	{
		UE_LOG(LogTemp, Warning, TEXT("Your inventory is full!"));
		InventoryOwner->OnItemTransferFailed();
		return;
	}

	InteractingInventory->AddToInventory(ItemData, ItemQuantity);
	UE_LOG(LogTemp, Warning, TEXT("%d of %s added to the %s"), ItemQuantity, *ItemData->ItemInfo.Name, *InteractingInventory->GetOwner()->GetActorNameOrLabel());
	InventoryOwner->OnItemTransferSuccess();
	Destroy();
}

FString APickupItem::GetInteractableName()
{
	return ItemData->ItemInfo.Name;
}


