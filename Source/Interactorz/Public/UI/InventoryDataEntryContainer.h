// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryDataEntryContainer.generated.h"

class UDA_ItemData;
class UImage;
class UTextBlock;

USTRUCT(Blueprintable)
struct FInventoryEntryDataContainer
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "UI | Inventory")
	UTexture2D* ItemIcon;

	UPROPERTY(BlueprintReadWrite, Category = "UI | Inventory")
	FString ItemName;

	UPROPERTY(BlueprintReadWrite, Category = "UI | Inventory")
	int32 ItemQuantity;
		
};
	
UCLASS(Blueprintable, BlueprintType)
class INTERACTORZ_API UInventoryDataEntryContainer : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite, Category = "UI | Inventory")
	FInventoryEntryDataContainer DataEntryContainer;

	UFUNCTION(BlueprintCallable, Category = "UI | Inventory")
	FInventoryEntryDataContainer SetDataEntryContainer(UTexture2D* ItemIcon, FString ItemName, int32 ItemQuantity);
};
