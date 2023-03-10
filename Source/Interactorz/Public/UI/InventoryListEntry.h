// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "InventoryListEntry.generated.h"

class UImage;
class UCanvasPanel;
class UTextBlock;
class UDAItemData;
UCLASS()
class INTERACTORZ_API UInventoryListEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* NameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* QuantityText;

	UPROPERTY(BlueprintReadWrite, Category = "UI | InventoryData")
	UDAItemData* Item;

public:
	UFUNCTION(BlueprintPure, Category = "UI | InventoryData")
	UDAItemData* GetItemData() const { return Item; }
};


