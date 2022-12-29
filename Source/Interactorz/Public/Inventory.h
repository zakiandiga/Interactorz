// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

UENUM(Blueprintable)
enum class EItemProcessType : uint8
{
	EIP_Drop UMETA(DisplayName = "Drop"),
	EIP_Consume UMETA(DisplayName = "Consume"),
	EIP_Equip UMETA(DisplayName = "Equip"),
	EIP_Remove UMETA(DisplayName = "Remove"),
	EIP_Retrieve UMETA(DisplayName = "Retrieve")
};

class UDA_ItemData;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTERACTORZ_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventory();

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Inventory Properties")
	TMap<UDA_ItemData*, int32> ActiveInventory = TMap<UDA_ItemData*, int32>();

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Inventory Properties")
	int32 InventoryLimit = 20;

	FVector DropLocationOffset = FVector(100, 100, 0);

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"), Category = "Inventory")
	void AddToInventory(UDA_ItemData* ItemToAdd, int32 QuantityToAdd);

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"), Category = "Inventory")
	void RemoveFromInventory(UDA_ItemData* ItemToRemove, int32 QuantityToRemove);	

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"), Category = "Inventory")
	void DropItem(UDA_ItemData* ItemToDrop, int32 QuantityToDrop);
	
	void ConsumeItem();
	void EquipItem();

public:
	UFUNCTION(BlueprintCallable)
	void ProcessItem(EItemProcessType ProcessType, UDA_ItemData* ItemToProcess, int32 QuantityToProcess);
	
	UFUNCTION(BlueprintPure, Category = "Inventory")
	FORCEINLINE TMap<UDA_ItemData*, int32> GetActiveInventory() const { return ActiveInventory; }

	UFUNCTION(BlueprintPure)
	bool CheckItemAvailable(UDA_ItemData* ItemToCheck) const;

	UFUNCTION(BlueprintPure)
	int32 CheckSpaceAvailable() const;

	UFUNCTION(BlueprintPure)
	int32 CheckItemQuantityInInventory(UDA_ItemData* ItemToCheck) const;


};
