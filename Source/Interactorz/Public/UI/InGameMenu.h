// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameMenu.generated.h"

class UCanvasPanel;
class UListView;
class UInventory;
class UInventoryListEntry;
class UWidgetSwitcher;

UCLASS()
class INTERACTORZ_API UInGameMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetMainPanelVisible();
	void SetMainPanelHidden();

	void DisplayInventoryList();
	void ClearInventoryList();

	UFUNCTION(BlueprintCallable, Category = "UI | Inventory")
	void OnListViewClicked(UObject* ClickedObject);
	
	UPROPERTY(BlueprintReadOnly, Category = "UI | Inventory")
	UInventory* OwnerInventory;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UI | Inventory")
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UI | Inventory")
	UCanvasPanel* MainPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UI | Inventory")
	UCanvasPanel* InventoryPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UI | Inventory")
	UListView* InventoryList;

	FORCEINLINE void SetOwnerInventory(UInventory* InventoryToSet) { OwnerInventory = InventoryToSet; }
};
