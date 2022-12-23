// Fill out your copyright notice in the Description page of Project Settings.


#include "GatheringSpot.h"
#include "Components/SphereComponent.h"
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
}

void AGatheringSpot::BeginOverlapDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AGatheringSpot::EndOverlapDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

bool AGatheringSpot::CanInteract(const AActor* InteractingActor)
{
	//true condition:
	//1. player in range
	//2. bISGatherable = true
	//3. OPTIONAL - player use correct tool

	return false;
}

void AGatheringSpot::Interact()
{
}

FString AGatheringSpot::GetInteractableName()
{
	return FString();
}
