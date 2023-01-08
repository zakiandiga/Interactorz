// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionHandler.generated.h"

class IInteractable;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionEnds);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTERACTORZ_API UInteractionHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionHandler();

private:
	IInteractable* CurrentInteractable = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	FString InteractableName = FString();

	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	bool bIsInteracting = false;

public:	
	
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void InitiateInteraction();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void EndingInteraction();

	UFUNCTION(BlueprintPure, Category = "Interaction")
	bool TrySetInteractable(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	FORCEINLINE void ClearInteractable() { CurrentInteractable = nullptr; }

	UFUNCTION(BlueprintPure, Category = "Interaction")
	FString GetInteractableName();
	
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionEnds OnInteractionEnds;
};
