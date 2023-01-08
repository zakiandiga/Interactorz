// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "Interfaces/InventoryOwner.h"
#include "StorageActor.generated.h"

class UInventory;
class UDAItemData;
UCLASS()
class INTERACTORZ_API AStorageActor : public AActor, public IInteractable, public IInventoryOwner
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStorageActor();

private:
	UPROPERTY(EditAnywhere, meta = (AllowAPrivateAccess = "true"), Category = "Storage Components")
	UStaticMeshComponent* StorageMesh;

	UPROPERTY(EditAnywhere, meta = (AllowAPrivateAccess = "true"), Category = "Storage Components")
	UInventory* StorageInventory;

	IInventoryOwner* CurrentInteractingInventoryOwner;

	UPROPERTY(EditAnywhere, meta = (AllowAPrivateAccess = "true"), Category = "Storage Components")
	UDAItemData* DEBUGITEMTOGIVE;
	UPROPERTY(EditAnywhere, meta = (AllowAPrivateAccess = "true"), Category = "Storage Components")
		int32 DEBUGITEMQUANTITY;

protected:

	virtual void BeginPlay() override;

	//should be called from a button/input
	UFUNCTION(BlueprintCallable, Category = "Storage | Item Transfer")
	void TransferToInteractor(UDAItemData* ItemToGive, int32 QuantityToGive);
	UFUNCTION(BlueprintCallable, Category = "Storage | Item Transfer")
	void TransferFromInteractor(UDAItemData* ItemToGet, int32 QuantityToGet);

public:	

	virtual void Tick(float DeltaTime) override;


	// Inherited via IInteractable
	UFUNCTION(BlueprintCallable, Category = "Interactable")
	bool CanInteract(const AActor* InteractingActor) override;

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	void Interact(AActor* InteractingActor) override;

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	FString GetInteractableName() override;

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	FOnInteractionFinished& OnInteractionFinished() override { return OnInteractionFinishedDelegate; }


	// Inherited via IInventoryOwner
	virtual UInventory* GetInventory() const override { return StorageInventory; }

	virtual void OnItemTransferSuccess() override;

	virtual void OnItemTransferFailed() override;

};
