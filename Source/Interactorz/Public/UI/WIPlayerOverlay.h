// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WIPlayerOverlay.generated.h"

class UCanvasPanel;
class UTextBlock;
class UInventory;
UCLASS()
class INTERACTORZ_API UWIPlayerOverlay : public UUserWidget
{
	GENERATED_BODY()	

private:

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* InteractableInfoPanel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* InteractableInfoText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Inventory")
	UInventory* PlayerInventory;

	UFUNCTION()
	void ItemRetrievedDelegate(FString Item, int32 Quantity);

	UFUNCTION()
	void ItemRemovedDelegate(FString Item, int32 Quantity);

	UFUNCTION()
	void ItemDroppedDelegate(FString Item, int32 Quantity);

	UFUNCTION()
	void ItemUsedDelegate(FString Item, int32 Quantity);

protected:
	void NativeConstruct() override;

public:

	UFUNCTION()
	void SetInteractableInfoPanelVisible(FString InteractableNameToSet);

	UFUNCTION()
	void SetInteractableInfoPanelHidden(FString InteractableNameToRemove);

	UFUNCTION(BlueprintNativeEvent, Category = "Inventory")
	void ItemRetrieved(const FString& ItemName, int32 Quantity);
	//void ItemRetrieved_Implementation(FString& ItemName, int32& Quantity);
		
	UFUNCTION(BlueprintNativeEvent, Category = "Inventory")
	void ItemRemoved(const FString& ItemName, int32 Quantity);

	UFUNCTION(BlueprintNativeEvent, Category = "Inventory")
	void ItemDropped(const FString& ItemName, int32 Quantity);

	UFUNCTION(BlueprintNativeEvent, Category = "Inventory")
	void ItemUsed(const FString& ItemName, int32 Quantity);	

	UFUNCTION(BlueprintNativeEvent, Category = "Inventory")
	void InventoryIsFull();
};