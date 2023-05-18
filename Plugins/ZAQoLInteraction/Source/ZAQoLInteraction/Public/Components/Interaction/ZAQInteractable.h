// Copyright Zaki Agraraharja. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZAQInteractable.generated.h"

/// <summary>
/// Base component to make an Actor interactable.
/// Extend this Actor Component to make a custom interactable implementation.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <param name=""></param>

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionFinished, AActor*, InteractedActor);
UCLASS( Blueprintable, ClassGroup=("ZAQoLInteraction"), meta = (DisplayName = "Interactable", BlueprintSpawnableComponent))
class ZAQOLINTERACTION_API UZAQInteractable : public UActorComponent
{
	GENERATED_BODY()

public:	
	UZAQInteractable();

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Interaction Handler")
	bool bShouldAutoFinish = true;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Interaction Handler")
	bool bIsInteracting = false;


public:	
	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	bool CanInteract(const AActor* InteractingActor);

	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void Interact(AActor* InteractingActor);

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	void FinishedInteraction();
	
	UFUNCTION(BlueprintPure, Category = "Interactable")
	FName GetInteractableName();

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	void SetAutoFinish(const bool ShouldAutoFinish) { bShouldAutoFinish = ShouldAutoFinish; }
	
	UFUNCTION(BlueprintCallable, Category = "Interactable")
	bool IsAutoFinish() { return bShouldAutoFinish; }

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	void SetInteracting(const bool bNewInteracting) { bIsInteracting = bNewInteracting; }

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	bool IsInteracting() { return bIsInteracting; }

	virtual bool CanInteract_Implementation(const AActor* InteractingActor);
	virtual void Interact_Implementation(AActor* InteractingActor);
			
	UPROPERTY(BlueprintAssignable, Category = "Interactable")
	FOnInteractionFinished OnInteractionFinished;
};
