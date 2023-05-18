// Copyright Zaki Agraraharja. All Rights Reserved.

#include "Components/Interaction/ZAQInteractionHandler.h"
#include "Components/Interaction/ZAQInteractable.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"

UZAQInteractionHandler::UZAQInteractionHandler()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UZAQInteractionHandler::InitiateInteraction()
{
	if (AssignedInteractableComponent == nullptr) return;
	
	AssignedInteractableComponent->OnInteractionFinished.AddUniqueDynamic(this, &UZAQInteractionHandler::EndInteraction);
	AssignedInteractableComponent->Interact(GetOwner());
}

void UZAQInteractionHandler::EndInteraction(AActor* InteractedActor)
{	
	AssignedInteractableComponent->OnInteractionFinished.RemoveDynamic(this, &UZAQInteractionHandler::EndInteraction);
	ClearInteractable();
	OnInteractionEnds.Broadcast();
}

void UZAQInteractionHandler::AssignInteractable(AActor* ActorToAssign)
{	
	if (!IsInteractable(ActorToAssign)) return;

	AssignedInteractableComponent = Cast<UZAQInteractable>(ActorToAssign->GetComponentByClass(UZAQInteractable::StaticClass()));
	SetCurrentInteractableActor(ActorToAssign);
}

void UZAQInteractionHandler::ClearInteractable()
{
	AssignedInteractableComponent = nullptr;
	SetCurrentInteractableActor(nullptr);
}

bool UZAQInteractionHandler::IsInteractable(AActor* ActorToCheck)
{
	UZAQInteractable* InteractableComponent;
	InteractableComponent = Cast<UZAQInteractable>(ActorToCheck->GetComponentByClass(UZAQInteractable::StaticClass()));
	return InteractableComponent != nullptr;
}



