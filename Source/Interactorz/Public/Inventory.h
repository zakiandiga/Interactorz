// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

class UDAItemData;

UENUM(Blueprintable)
enum class EItemProcessType : uint8
{
	EIP_Drop UMETA(DisplayName = "Drop"),
	EIP_Use UMETA(DisplayName = "Use"),
	EIP_Remove UMETA(DisplayName = "Remove"),
	EIP_Retrieve UMETA(DisplayName = "Retrieve")
};

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_USTRUCT_BODY()

	UDAItemData* Item;
	int32 ItemQuantity;

	UDAItemData* SetItem(UDAItemData* ItemToSet) { Item = ItemToSet; }
	int32 SetItemQuantity(int32 QuantityToSet) { ItemQuantity = QuantityToSet; }

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemProcessed, FString, ItemName, int32, ItemQuantity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryIsFull);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTERACTORZ_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventory();

private:

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Inventory Properties")
	TMap<UDAItemData*, int32> ActiveInventory = TMap<UDAItemData*, int32>();

	//UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Inventory Properties")
	//TSet<FInventoryItem> InventoryItems = TSet<FInventoryItem>();

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Inventory Properties")
	int32 MaxInventorySpace = 20;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Inventory Properties")
	int32 UsedInventorySpace = 0;

	UPROPERTY()
	FVector DropLocationOffset = FVector(100, 100, 0);

	UFUNCTION()
	void UpdateInventorySpace();

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"), Category = "Inventory")
	void AddToInventory(UDAItemData* ItemToAdd, int32 QuantityToAdd);

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"), Category = "Inventory")
	void RemoveFromInventory(UDAItemData* ItemToRemove, int32 QuantityToRemove);	

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"), Category = "Inventory")
	void DropItem(UDAItemData* ItemToDrop, int32 QuantityToDrop);
	
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"), Category = "Inventory")
	void UseItem(UDAItemData* ItemToUse, int32 QuantityToUse);

	UFUNCTION()
	void SpawnItemToWorld(UDAItemData* ItemToDrop, const int32 Quantity);

public:
	UFUNCTION(BlueprintCallable)
	void ProcessItem(EItemProcessType ProcessType, UDAItemData* ItemToProcess, int32 QuantityToProcess);
	
	UFUNCTION(BlueprintPure, Category = "Inventory")
	TMap<UDAItemData*, int32> GetActiveInventory() const { return ActiveInventory; }

	UFUNCTION(BlueprintPure)
	bool CheckItemAvailable(UDAItemData* ItemToCheck) const;

	UFUNCTION(BlueprintPure)
	int32 CheckSpaceAvailable() const;

	UFUNCTION(BlueprintPure)
	int32 CheckItemQuantityInInventory(UDAItemData* ItemToCheck) const;

	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "Inventory Update")
	FOnItemProcessed OnItemRetrieved;

	UPROPERTY(BlueprintAssignable, Category = "Inventory Update")
	FOnItemProcessed OnItemRemoved;

	UPROPERTY(BlueprintAssignable, Category = "Inventory Update")
	FOnItemProcessed OnItemUsed;

	UPROPERTY(BlueprintAssignable, Category = "Inventory Update")
	FOnItemProcessed OnItemDropped;

	UPROPERTY(BlueprintAssignable, Category = "Inventory Update")
	FOnInventoryIsFull OnInventoryIsFull;
};
