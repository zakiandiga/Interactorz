// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryEntryDataContainer.generated.h"

class UDAItemData;
class UImage;
class UTextBlock;

USTRUCT(Blueprintable)
struct FInventoryDataContainer
{
	GENERATED_USTRUCT_BODY()


	UPROPERTY(BlueprintReadWrite, Category = "UI | Inventory")
	UDAItemData* Item = nullptr;
		
	UPROPERTY(BlueprintReadWrite, Category = "UI | Inventory")
	int32 ItemQuantity = 0;
};
	
UCLASS(Blueprintable, BlueprintType)
class INTERACTORZ_API UInventoryEntryDataContainer : public UObject
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "UI | Inventory")
	FInventoryDataContainer InventoryDataContainer;

public:
	
	UFUNCTION(BlueprintCallable, Category = "UI | Inventory")
	void SetDataContainer(UDAItemData* ItemData, int32 ItemQuantity);

	UFUNCTION()
	FInventoryDataContainer GetDataContainer() { return InventoryDataContainer; }

	UFUNCTION()
	void SetDataQuantity(int32 NewQuantity) { InventoryDataContainer.ItemQuantity = NewQuantity; }
};
