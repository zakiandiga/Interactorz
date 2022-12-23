// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "Interfaces/Interactable.h"
#include "NPC.generated.h"

class USkeletalMeshComponent;
UCLASS()
class INTERACTORZ_API ANPC : public APawn, public IInteractable
{
	GENERATED_BODY()

public:
	ANPC();
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;	

	UFUNCTION(BlueprintCallable)
	bool CanInteract(const AActor* InteractingActor) override;

	UFUNCTION(BlueprintCallable)
	void Interact(AActor* InteractingActor) override;

	FString GetInteractableName() override;

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	USkeletalMeshComponent* BodyMesh;
};
