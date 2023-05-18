// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionHandler.h"
#include "Interfaces/Interactable.h"

// Sets default values for this component's properties
UInteractionHandler::UInteractionHandler()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractionHandler::InitiateInteraction()
{
	if (CurrentInteractable == nullptr) return;
	
	CurrentInteractable->OnInteractionFinished().BindDynamic(this, &UInteractionHandler::EndingInteraction);
	CurrentInteractable->Interact(GetOwner());
}

void UInteractionHandler::EndingInteraction()
{
	CurrentInteractable->OnInteractionFinished().Unbind();
	ClearInteractable();
	OnInteractionEnds.Broadcast();
}

bool UInteractionHandler::TrySetInteractable(AActor* ActorToInteract)
{
	CurrentInteractable = Cast<IInteractable>(ActorToInteract);

	return CurrentInteractable == nullptr ? false : true;
}

FName UInteractionHandler::GetInteractableName()
{
	/*
	if (CurrentInteractable == nullptr)
	{
		return FString("ERROR: Interactable name not assigned!");
	}
	*/
	return FName(CurrentInteractable->GetInteractableName());
}
