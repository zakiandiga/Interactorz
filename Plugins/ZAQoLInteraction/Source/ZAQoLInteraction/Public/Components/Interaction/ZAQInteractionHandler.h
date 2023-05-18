// Copyright Zaki Agraraharja. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZAQInteractionHandler.generated.h"

class UZAQInteractable;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FQIOnInteractionEnds);
UCLASS(Blueprintable, ClassGroup = ("ZAQoLInteraction"), meta = (BlueprintSpawnableComponent))
class ZAQOLINTERACTION_API UZAQInteractionHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	UZAQInteractionHandler();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Interaction Handler")
	AActor* CurrentInteractableActor = nullptr;

	UPROPERTY()
	UZAQInteractable* AssignedInteractableComponent = nullptr;


public:
	/// <summary>
	/// Assign interactable actor that's ready for interaction
	/// </summary>
	/// <param name="InteractableToAssign"></param>
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void AssignInteractable(AActor* ActorToInteract);

	UFUNCTION(Category = "Interaction Handler")
	void ClearInteractable();

	UFUNCTION(BlueprintCallable, Category = "Interaction Handler")
	void InitiateInteraction();

	UFUNCTION(BlueprintCallable, Category = "Interaction Handler")
	void EndInteraction(AActor* InteractedActor);
	
	UFUNCTION(BlueprintPure, Category = "Interaction Handler")
	bool IsInteractable(AActor* ActorToCheck);

	UFUNCTION(BlueprintPure, Category = "Interaction Handler")
	AActor* GetCurrentInteractableActor() { return CurrentInteractableActor; }
	
	UFUNCTION(BlueprintCallable, Category = "Interaction Handler")
	void SetCurrentInteractableActor(AActor* ActorToSet) { CurrentInteractableActor = ActorToSet; }

	UPROPERTY(BlueprintAssignable, Category = "Interaction Handler")
	FQIOnInteractionEnds OnInteractionEnds;		
};
