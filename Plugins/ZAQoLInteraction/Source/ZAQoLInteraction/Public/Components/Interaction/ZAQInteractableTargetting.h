// Copyright Zaki Agraraharja. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZAQInteractableTargetting.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UZAQInteractable;
class UZAQInteractableCollider;
class UZAQInteractionHandler;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractableFound, AActor*, InteractableActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractableGone);
UCLASS(Blueprintable, ClassGroup = ("ZAQoLInteraction"), meta = (DisplayName = "Interactable Targetting", BlueprintSpawnableComponent))
class ZAQOLINTERACTION_API UZAQInteractableTargetting : public UActorComponent
{
	GENERATED_BODY()

public:	
	UZAQInteractableTargetting();

private:
	UCameraComponent* PlayerCamera = nullptr;
	USpringArmComponent* CameraBoom = nullptr;

	UZAQInteractionHandler* InteractionHandler;
	UZAQInteractableCollider* InteractableCollider;

	TSubclassOf<UZAQInteractable>* InteractableClass;

	void TryAssignInteractable(AActor* ActorToTry);

	bool IsTracing() const;

protected:
	UPROPERTY(EditInstanceOnly, Category = "Interactable Targetting")
	float TracingRange = 400.f;

	virtual void BeginPlay() override;

	UFUNCTION()
	void TracingInteractable();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category = "Interactable Targetting")
	FOnInteractableFound OnInteractableFound;

	UPROPERTY(BlueprintAssignable, Category = "Interactable Targetting")
	FOnInteractableGone OnInteractableGone;
};
