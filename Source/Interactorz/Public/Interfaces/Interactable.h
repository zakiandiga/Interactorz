// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class INTERACTORZ_API IInteractable
{
	GENERATED_BODY()

public:
	virtual bool CanInteract(const AActor* InteractingActor) = 0;

	virtual void Interact() = 0;

	virtual FString GetInteractableName() = 0;

};
