// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryDataEntryContainer.generated.h"

class UDA_ItemData;
class UImage;
class UTextBlock;

USTRUCT(Blueprintable)
struct FInventoryDataContainer
{
	GENERATED_USTRUCT_BODY()


	UPROPERTY(BlueprintReadWrite, Category = "UI | Inventory")
	UDA_ItemData* Item;
		
	UPROPERTY(BlueprintReadWrite, Category = "UI | Inventory")
	int32 ItemQuantity;
};
	
UCLASS(Blueprintable, BlueprintType)
class INTERACTORZ_API UInventoryDataEntryContainer : public UObject
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "UI | Inventory")
	FInventoryDataContainer InventoryDataContainer;

public:
	
	UFUNCTION(BlueprintCallable, Category = "UI | Inventory")
	void SetDataEntryContainer(UDA_ItemData* ItemData, int32 ItemQuantity);

	UFUNCTION()
	FInventoryDataContainer GetDataEntryContainer() { return InventoryDataContainer; }

	UFUNCTION()
	void SetDataQuantity(int32 NewQuantity) { InventoryDataContainer.ItemQuantity = NewQuantity; }
};
