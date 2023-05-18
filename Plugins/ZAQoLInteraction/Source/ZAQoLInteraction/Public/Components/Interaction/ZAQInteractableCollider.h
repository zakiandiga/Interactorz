// Copyright Zaki Agraraharja. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "ZAQInteractableCollider.generated.h"

class UZAQInteractionHandler;

/**
 An extension of USphereComponent with the Interactable detecting system
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractableUpdated);
UCLASS(ClassGroup = "ZAQoLInteraction", editinlinenew, hidecategories = (Object, LOD, Lighting, TextureStreaming), meta = (DisplayName = "Interactable Detector", BlueprintSpawnableComponent))
class ZAQOLINTERACTION_API UZAQInteractableCollider : public USphereComponent
{
	GENERATED_BODY()
	
public:
	UZAQInteractableCollider();

private:
	UZAQInteractionHandler* InteractionHandlerComponent = nullptr;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Interactable")
	TSet<AActor*> CurrentInteractableActorsInRange = TSet<AActor*>();

public:
	UFUNCTION(BlueprintPure, Category = "Interactable")
	bool HasOverlappingActors();

	UFUNCTION(BlueprintPure, Category = "Interactable")
	TSet<AActor*> InteractableActorsInRange() { return CurrentInteractableActorsInRange; }
	
	UFUNCTION(BlueprintCallable, Category = "Interactable")
	void UpdateOverlappingActorsTSet();

	UPROPERTY(BlueprintAssignable, Category = "Interactable")
	FOnInteractableUpdated OnInteractableEnter;

	UPROPERTY(BlueprintAssignable, Category = "Interactable")
	FOnInteractableUpdated OnInteractableExit;
	
};
