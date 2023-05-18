// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WIInGameMenu.generated.h"

class UCanvasPanel;
class UListView;
class UInventory;
class UInventoryListEntry;
class UWIWidgetSwitcher;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMenuCreated, UUserWidget*, Root);
UCLASS()
class INTERACTORZ_API UWIInGameMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetMainPanelVisible();
	void SetMainPanelHidden();
	
	UPROPERTY(BlueprintReadOnly, Category = "UI | Inventory")
	UInventory* OwnerInventory;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UI | Inventory")
	UWIWidgetSwitcher* PageSwitcher;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UI | Inventory")
	UCanvasPanel* MainPanel;

	FORCEINLINE UInventory* GetOwnerInventory() { return OwnerInventory; }
	FORCEINLINE void SetOwnerInventory(UInventory* InventoryToSet) { OwnerInventory = InventoryToSet; }

	FOnMenuCreated OnMenuCreated;
};
