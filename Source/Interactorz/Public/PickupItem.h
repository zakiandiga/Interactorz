// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "Interfaces/Interactable.h"
#include "PickupItem.generated.h"

class UStaticMeshComponent;
class UDA_ItemData;
UCLASS()
class INTERACTORZ_API APickupItem : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	APickupItem();

protected:

	virtual void BeginOverlapDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void EndOverlapDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UFUNCTION(BlueprintCallable)
	bool CanInteract(const AActor* InteractingActor) override;

	UFUNCTION(BlueprintCallable)
	void Interact(AActor* InteractingActor) override;

	FString GetInteractableName() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UStaticMeshComponent* ItemSprite;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	UDA_ItemData* ItemData;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	int32 ItemQuantity = 1;

	TSubclassOf<AActor*> Player;
	
};
