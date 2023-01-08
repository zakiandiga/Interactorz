// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Interactable.h"
#include "PickupItem.generated.h"

class UStaticMeshComponent;
class UDAItemData;
UCLASS()
class INTERACTORZ_API APickupItem : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	APickupItem();

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UStaticMeshComponent* ItemSprite;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	UDAItemData* ItemData;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	int32 ItemQuantity = 1;

	TSubclassOf<AActor*> Player;

	bool bCreatedFromSpawn = false;


public:
	void SpawnInitialize(UDAItemData* ItemDataToSet, int32 QuantityToSet);

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	bool CanInteract(const AActor* InteractingActor) override;

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	void Interact(AActor* InteractingActor) override;

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	FString GetInteractableName() override;

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	FOnInteractionFinished& OnInteractionFinished() override { return OnInteractionFinishedDelegate; }
};
