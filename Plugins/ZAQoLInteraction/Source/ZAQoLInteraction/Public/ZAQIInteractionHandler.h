// Copyright Zaki Agraraharja. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZAQIInteractionHandler.generated.h"

//class IZAQIInteractable;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FQIOnInteractionEnds);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZAQOLINTERACTION_API UZAQIInteractionHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	UZAQIInteractionHandler();

private:

	UObject* CurrentInteractableObject = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Interaction Handler")
	FString InteractableName = FString();

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Interaction Handler")
	bool bIsAutoFinish = true;

public:

	UFUNCTION(BlueprintCallable, Category = "Interaction Handler")
	void InitiateInteraction();

	UFUNCTION(BlueprintCallable, Category = "Interaction Handler")
	void EndingInteraction();

	UFUNCTION(BlueprintPure, Category = "Interaction Handler")
	bool TrySetInteractable(AActor* ActorToInteract);

	UFUNCTION(BlueprintCallable, Category = "Interaction Handler")
	void ClearInteractable() { CurrentInteractableObject = nullptr; }

	UFUNCTION(BlueprintPure, Category = "Interaction Handler")
	FString GetInteractableName();

	UFUNCTION(BlueprintPure, Category = "Interaction Handler")
	bool GetAutoFinish() const { return bIsAutoFinish; }

	UFUNCTION(BlueprintCallable, Category = "Interaction Handler")
	void SetAutoFinish(const bool ShouldAutoFinish) { bIsAutoFinish = ShouldAutoFinish; }

	UPROPERTY(BlueprintAssignable, Category = "Interaction Handler")
	FQIOnInteractionEnds OnInteractionEnds;

		
};
