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
	InteractableCollider->SetupAttachment(ItemSprite);
	
}

void APickupItem::BeginPlay()
{
	Super::BeginPlay();
}

void APickupItem::BeginOverlapDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::BeginOverlapDelegate(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);	

}

void APickupItem::EndOverlapDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::EndOverlapDelegate(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

bool APickupItem::CanInteract(const AActor* InteractingActor)
{
	return InteractingActor == GetCurrentInteractableActor();
}

void APickupItem::Interact()
{	
	UInventory* InteractingActorInventory = Cast<IInventoryOwner>(GetCurrentInteractableActor())->GetActorInventory();
	if (InteractingActorInventory == nullptr) return;
	
	if (InteractingActorInventory->CheckSpaceAvailable() < ItemQuantity)
	{
		UE_LOG(LogTemp, Warning, TEXT("Your inventory is full!"));
		return;
	}

	InteractingActorInventory->AddToInventory(ItemData, ItemQuantity);
	UE_LOG(LogTemp, Warning, TEXT("%d of %s added to the %s"), ItemQuantity, *ItemData->ItemInfo.Name, *InteractingActorInventory->GetOwner()->GetActorNameOrLabel());

	Destroy();
}

FString APickupItem::GetInteractableName()
{
	return ItemData->ItemInfo.Name;
}


