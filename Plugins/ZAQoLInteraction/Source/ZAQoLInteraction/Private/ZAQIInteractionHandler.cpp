// Copyright Zaki Agraraharja. All Rights Reserved.

#include "ZAQIInteractionHandler.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/ZAQIInteractable.h"


UZAQIInteractionHandler::UZAQIInteractionHandler()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UZAQIInteractionHandler::InitiateInteraction()
{
	if (CurrentInteractableObject == nullptr) return;
	
	IZAQIInteractable::Execute_Interact(CurrentInteractableObject, GetOwner());

	if (!bIsAutoFinish) return;
		
	EndingInteraction();
}

void UZAQIInteractionHandler::EndingInteraction()
{	
	UE_LOG(LogTemp, Warning, TEXT("Finished interaction with interactable : %s"), *GetInteractableName());
	ClearInteractable();
	OnInteractionEnds.Broadcast();
}

bool UZAQIInteractionHandler::TrySetInteractable(AActor* ActorToInteract)
{
	if (UKismetSystemLibrary::DoesImplementInterface(ActorToInteract, UZAQIInteractable::StaticClass()))
	{
		CurrentInteractableObject = ActorToInteract;
		return true;
	}

	return false;
}

FString UZAQIInteractionHandler::GetInteractableName()
{
	if (CurrentInteractableObject == nullptr)
	{
		return FString("ERROR: Interactable name not assigned!");
	}

	return IZAQIInteractable::Execute_GetInteractableName(CurrentInteractableObject);
}


