// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WPanelInventory.generated.h"

class UCanvasPanel;
class UInventory;
class UListView;
class UInventoryListEntry;
UCLASS()
class INTERACTORZ_API UWPanelInventory : public UUserWidget
{
	GENERATED_BODY()
	

private:
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "UI | Inventory")
	UInventory* OwnerInventory;


public:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UI | Inventory")
	UListView* InventoryList;

	FORCEINLINE void SetOwnerInventory(UInventory* InventoryToSet) { OwnerInventory = InventoryToSet; }
};
