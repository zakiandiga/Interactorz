// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "InventoryListEntry.generated.h"

class UImage;
class UCanvasPanel;
class UTextBlock;
//class IUserObjectListEntry;

UCLASS()
class INTERACTORZ_API UInventoryListEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetInventoryDataEntry(UTexture2D* IconToSet, FString NameToSet, int32 QuantityToSet);

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UImage* ItemIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* NameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* QuantityText;

};


