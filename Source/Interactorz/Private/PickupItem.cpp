// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItem.h"
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
	//InteractableCollider->SetupAttachment(ItemSprite);	
	ItemSprite->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
}


void APickupItem::BeginOverlapDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Super::BeginOverlapDelegate(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);	

}

void APickupItem::EndOverlapDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//Super::EndOverlapDelegate(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
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


