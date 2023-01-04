// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/IUISwitcherListener.h"
#include "WPanelInventory.generated.h"

class UWidget;
class UInGameMenu;
class UCanvasPanel;
class UInventory;
class UListView;
class UInventoryListEntry;
class UTextBlock;
UCLASS()
class INTERACTORZ_API UWPanelInventory : public UUserWidget, public IIUISwitcherListener
{
	GENERATED_BODY()
	

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "UI | Inventory")
	int32 SelectedInventoryListIndex = 0;

	UPROPERTY()
	UObject* SelectedItemFromInventory = nullptr;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "UI | Inventory")
	UInventory* OwnerInventory;

	void NativeConstruct() override;
	
	UFUNCTION()
	void AssignOwnerInventory(UInGameMenu* Root);

	bool ShouldCycleTargetIndex(int32 TargetIndex);
	int32 CycleNextIndex(int32 TargetIndex);	

public:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UI | Inventory")
	UListView* InventoryList;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UI | Inventory")
	UTextBlock* DescriptionText;

	void OnPageOpened_Implementation(UWidget* OpenedWidget) override;
	void OnPageClosed_Implementation(UWidget* ClosedWidget) override;

	UFUNCTION(BlueprintCallable, Category = "UI | Inventory")
	void OnListViewClicked(UObject* ClickedObject);

	UFUNCTION(BlueprintCallable, Category = "UI | Inventory")
	void DisplayInventoryList();

	UFUNCTION(BlueprintCallable, Category = "UI | Inventory")
	void ClearInventoryList();

	UFUNCTION(BlueprintCallable, Category = "UI | Navigation")
	void SelectCurrentItem(UObject* SelectedItem, bool IsSelected);

	UFUNCTION(BlueprintCallable, Category = "UI | Navigation")
	void SelectionChange(float Value);

	UFUNCTION(BlueprintCallable, Category = "UI | Inventory")
	void SetOwnerInventory(UInventory* InventoryToSet) { OwnerInventory = InventoryToSet; }

	UFUNCTION(BlueprintCallable, Category = "UI | Inventory")
	void SetSelectedInventoryListIndex(const int32 TargetIndex) { SelectedInventoryListIndex = TargetIndex; }

	UFUNCTION()
	void SetSelectedItemFromInventory(UObject* SelectedItem) { SelectedItemFromInventory = SelectedItem; }

	UFUNCTION(BlueprintPure, Category = "UI | Navigation")
	int32 GetSelectedInventoryListIndex() const { return SelectedInventoryListIndex; }

	UFUNCTION(BlueprintCallable, Category = "UI | Inventory")
	void SetDescriptionText(UObject* ObjectToSet);
	
};
