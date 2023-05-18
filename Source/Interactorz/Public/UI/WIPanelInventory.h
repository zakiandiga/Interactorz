// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/IUISwitcherListener.h"
#include "WIPanelInventory.generated.h"

class UWidget;
class UWIInGameMenu;
class UCanvasPanel;
class UListView;
class UInventoryListEntry;
class UTextBlock;
class UInventory;
class UDAItemData;
UCLASS()
class INTERACTORZ_API UWIPanelInventory : public UUserWidget, public IIUISwitcherListener
{
	GENERATED_BODY()
	
protected:
	bool bIsCurrentlyActive = false;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "UI | Inventory")
	int32 SelectedItemIndex = 0;

	UPROPERTY()
	UObject* SelectedItemObject = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "UI | Inventory")
	UInventory* OwnerInventory;

	bool ShouldCycleTargetIndex(int32 TargetIndex);

	int32 CycleNextIndex(int32 TargetIndex);

	void NativeConstruct() override;

	UFUNCTION()
	void DisplayInventoryList();

	UFUNCTION()
	void ClearInventoryList();

	UFUNCTION()
	void AssignOwnerInventory(UUserWidget* Root);

public:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UI | Inventory")
	UListView* InventoryList;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UI | Inventory")
	UTextBlock* DescriptionText;

	void OnPageOpened_Implementation(UWidget* OpenedWidget) override;
	void OnPageClosed_Implementation(UWidget* ClosedWidget) override;

	UFUNCTION(BlueprintCallable, Category = "UI | Inventory")
	void ProcessItem(UObject* ClickedObject, EItemProcessType ProcessType);

	UFUNCTION(BlueprintCallable, Category = "UI | Navigation")
	void SelectCurrentItem(UObject* SelectedItem, bool IsSelected);

	UFUNCTION(BlueprintCallable, Category = "UI | Navigation")
	void SelectionChange(float Value);

	UFUNCTION(BlueprintCallable, Category = "UI | Inventory")
	void SetOwnerInventory(UInventory* InventoryToSet) { OwnerInventory = InventoryToSet; }

	UFUNCTION(BlueprintCallable, Category = "UI | Inventory")
	UInventory* GetOwnerInventory() { return OwnerInventory; }

	UFUNCTION(BlueprintPure, Category = "UI | Navigation")
	int32 GetSelectedItemIndex() const { return SelectedItemIndex; }

	UFUNCTION(BlueprintCallable, Category = "UI | Inventory")
	void SetSelectedItemIndex(const int32 TargetIndex) { SelectedItemIndex = TargetIndex; }

	UFUNCTION(BlueprintCallable, Category = "UI | Inventory")
	FString GetItemDescriptionText(UObject* ObjectToSet);

	UFUNCTION(BlueprintCallable, Category = "UI | Inventory")
	void SetDescriptionText(UObject* ObjectToSet);

};
