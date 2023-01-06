// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/GatheringSpot.h"
#include "Kismet/GameplayStatics.h"
#include "DA_ItemData.h"
#include "Inventory.h"
#include "Interfaces/InventoryOwner.h"

AGatheringSpot::AGatheringSpot()
{
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Sprite"));
	ItemData = CreateDefaultSubobject<UDA_ItemData>(TEXT("Item Info"));

	SetRootComponent(ItemMesh);
}

void AGatheringSpot::BeginPlay()
{
	HealthPoint = MaxHealthPoint;
}


bool AGatheringSpot::CanInteract(const AActor* InteractingActor)
{
	//true condition:
	//1. player in range
	//2. bISGatherable = true
	//3. OPTIONAL - player use correct tool

	return false;
}

void AGatheringSpot::Interact(AActor* InteractingActor)
{
	CurrentItemQuantity = GetCurrentGatheringQuantity();

	InventoryOwner = Cast<IInventoryOwner>(InteractingActor);
	if (InventoryOwner == nullptr) return;

	UInventory* InteractingInventory = InventoryOwner->GetActorInventory();
	if (InteractingInventory == nullptr) return;

	if (InteractingInventory->CheckSpaceAvailable() < CurrentItemQuantity)
	{
		InventoryOwner->OnItemTransferFailed();
		return;
	}

	GetWorldTimerManager().SetTimer(GatheringTimer, this, &AGatheringSpot::OnGatheringDone, GatheringTime, false);
}

void AGatheringSpot::OnGatheringDone()
{
	InventoryOwner->GetActorInventory()->ProcessItem(EItemProcessType::EIP_Retrieve, ItemData, CurrentItemQuantity);
	InventoryOwner->OnItemTransferSuccess();
	InventoryOwner = nullptr;
	CurrentItemQuantity = 0;

	HealthPoint -= 1;

	if (HealthPoint <= 0)
	{
		ItemMesh->SetVisibility(false, true);
		GetWorldTimerManager().SetTimer(RespawnTimer, this, &AGatheringSpot::OnRespawn, RespawnTime, false);
	}
}

void AGatheringSpot::OnRespawn()
{
	HealthPoint = MaxHealthPoint;
	ItemMesh->SetVisibility(true, true);
}

FString AGatheringSpot::GetInteractableName()
{
	return SpotName;
}
