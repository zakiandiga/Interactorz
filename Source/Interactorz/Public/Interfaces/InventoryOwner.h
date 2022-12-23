// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventoryOwner.generated.h"

UINTERFACE(MinimalAPI)
class UInventoryOwner : public UInterface
{
	GENERATED_BODY()
};

class INTERACTORZ_API IInventoryOwner
{
	GENERATED_BODY()

public:
	virtual class UInventory* GetActorInventory() const = 0;
	virtual void OnItemTransferSuccess() = 0;
	virtual void OnItemTransferFailed() = 0;
};
