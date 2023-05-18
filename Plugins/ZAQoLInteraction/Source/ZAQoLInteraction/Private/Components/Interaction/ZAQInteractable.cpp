// Copyright Zaki Agraraharja. All Rights Reserved.

#include "Components/Interaction/ZAQInteractable.h"
#include "GameFramework/Actor.h"

UZAQInteractable::UZAQInteractable()
{
	PrimaryComponentTick.bCanEverTick = false;
}

FName UZAQInteractable::GetInteractableName()
{
	return FName(GetOwner()->GetName());
}

bool UZAQInteractable::CanInteract_Implementation(const AActor* InteractingActor)
{
	return !IsInteracting();
}

void UZAQInteractable::Interact_Implementation(AActor* InteractingActor)
{	
	UE_LOG(LogTemp, Display, TEXT("Default C++ Interact() implementation"));
	SetInteracting(true);

	//if !bShouldAutoFinish, make sure to call FinishInteraction().
	//this non-autofinish interactable is helpful to handle interaction that requires que from external event in order to finish, 
	//for example finishing the interaction after the set of dialogue of an NPC is displayed.
	FinishedInteraction();

	if (!bShouldAutoFinish) return;
	FinishedInteraction();
}

void UZAQInteractable::FinishedInteraction()
{
	SetInteracting(false);
	OnInteractionFinished.Broadcast(GetOwner());
}


