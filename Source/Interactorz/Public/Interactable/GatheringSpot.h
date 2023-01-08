// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Interactable.h"
#include "GatheringSpot.generated.h"

class UDAItemData;
class IInventoryOwner;

UCLASS()
class INTERACTORZ_API AGatheringSpot : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:
	AGatheringSpot();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Interactable")
	bool CanInteract(const AActor* InteractingActor) override;

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	void Interact(AActor* InteractingActor) override;

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	FString GetInteractableName() override;

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	FOnInteractionFinished& OnInteractionFinished() override { return OnInteractionFinishedDelegate; }

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	FString SpotName = FString();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UStaticMeshComponent* ItemMesh = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	UDAItemData* ItemData = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	int32 HealthPoint = 1;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	int32 MaxHealthPoint = 10;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	float GatheringTime = 2.f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	int32 MinimumGatheringQuantity = 1;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	int32 MaximumGatheringQuantity = 1;

	int32 CurrentItemQuantity;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	bool bCanRespawn = false;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	float RespawnTime = 10.f;

	bool bIsGatherable = false;

	IInventoryOwner* InventoryOwner = nullptr;

	FTimerHandle GatheringTimer;
	FTimerHandle RespawnTimer;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void OnGatheringDone();

	UFUNCTION(BlueprintCallable, Category = "respawn")
	void OnRespawn();

public:
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetCurrentGatheringQuantity() const { return MinimumGatheringQuantity != MaximumGatheringQuantity ? FMath::RandRange(MinimumGatheringQuantity, MaximumGatheringQuantity) : MaximumGatheringQuantity; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetHealthPoint() const { return HealthPoint; }

	

};
