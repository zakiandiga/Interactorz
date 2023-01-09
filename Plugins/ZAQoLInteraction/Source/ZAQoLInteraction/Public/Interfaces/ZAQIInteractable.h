// Copyright Zaki Agraraharja. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ZAQIInteractable.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UZAQIInteractable : public UInterface
{
	GENERATED_BODY()
};

class ZAQOLINTERACTION_API IZAQIInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactable")
	bool CanInteract(const AActor* InteractingActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactable")
	void Interact(AActor* InteractingActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactable")
	FString GetInteractableName();
};
