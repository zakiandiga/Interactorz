// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Interaction/ZAQPickupItem.h"

UZAQPickupItem::UZAQPickupItem() : UZAQInteractable()
{
	//whatever needs to be assign in the constructor
	SetAutoFinish(false);
}

void UZAQPickupItem::Interact_Implementation(AActor* InteractingActor)
{
	FString DebugMessage = TEXT("Pickup item is interacting with the player");
	float DisplayTime = 5.0f;
	FColor TextColor = FColor::Yellow;
	int32 Key = -1;

	GEngine->AddOnScreenDebugMessage(Key, DisplayTime, TextColor, DebugMessage);

	if (!CanPlayerPickup())
	{
		InventoryFullFollowup();
		return;
	}

	InventoryAvailableFollowup();
}

void UZAQPickupItem::InventoryFullFollowup()
{
	FString DebugMessage = TEXT("Player inventory is full, nothing happened!");
	float DisplayTime = 5.0f;
	FColor TextColor = FColor::Red;
	int32 Key = -1;

	GEngine->AddOnScreenDebugMessage(Key, DisplayTime, TextColor, DebugMessage);

	FinishedInteraction();
}

void UZAQPickupItem::InventoryAvailableFollowup()
{
	FString DebugMessage = TEXT("Player pickup the item, now destroy!");
	float DisplayTime = 5.0f;
	FColor TextColor = FColor::Green;
	int32 Key = -1;

	GEngine->AddOnScreenDebugMessage(Key, DisplayTime, TextColor, DebugMessage);

	FinishedInteraction();
	GetOwner()->Destroy();
}

