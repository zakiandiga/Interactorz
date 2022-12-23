// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

class UDA_ItemData;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTERACTORZ_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventory();

protected:
	virtual void BeginPlay() override;

public:	
	void AddToInventory(UDA_ItemData* ItemToAdd, int32 QuantityToAdd);

	void RemoveFromInventory(UDA_ItemData* ItemToRemove, int32 QuantityToRemove);	

private:

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Inventory Properties")
	TMap<UDA_ItemData*, int32> ActiveInventory;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Inventory Properties")
	int32 InventoryLimit = 20;

public:
	UFUNCTION(BlueprintPure)
	bool CheckItemAvailable(UDA_ItemData* ItemToCheck) const;

	UFUNCTION(BlueprintPure)
	int32 CheckSpaceAvailable() const;

	UFUNCTION(BlueprintPure)
	int32 CheckItemQuantityInInventory(UDA_ItemData* ItemToCheck) const;


};
