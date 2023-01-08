// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemAction.generated.h"

class UDAItemData;
UCLASS(Blueprintable)
class INTERACTORZ_API UItemAction : public UObject
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintNativeEvent, meta = (WorldContext = "WorldContextObject"), Category = "Item Action")
	void UseItem(UDAItemData* UsedItem, AActor* ItemUser);

	virtual void UseItem_Implementation(UDAItemData* UsedItem, AActor* ItemUser);

};
