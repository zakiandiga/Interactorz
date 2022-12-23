// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "Interfaces/Interactable.h"
#include "GatheringSpot.generated.h"

class UDA_ItemData;
UCLASS()
class INTERACTORZ_API AGatheringSpot : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:
	AGatheringSpot();

protected:
	virtual void BeginPlay() override;

	virtual void BeginOverlapDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void EndOverlapDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UFUNCTION(BlueprintCallable)
		bool CanInteract(const AActor* InteractingActor) override;

	UFUNCTION(BlueprintCallable)
		void Interact(AActor* InteractingActor) override;

	FString GetInteractableName() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	UDA_ItemData* ItemData;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	int32 GatheringLimit = 1;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	int32 MinimumItemGained = 1;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	int32 MaximumItemGained = 1;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	bool bCanRespawn = false;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	float RespawnTime = 1.f;

	bool bIsGatherable = false;

	TSubclassOf<AActor*> Player;

public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetItemGainedAmount() const { return MinimumItemGained != MaximumItemGained ? FMath::RandRange(MinimumItemGained, MaximumItemGained) : MaximumItemGained; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetGatheringLimit() const { return GatheringLimit; }

};
