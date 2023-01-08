// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	bool CanInteract(const AActor* InteractingActor) override;

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	void Interact(AActor* InteractingActor) override;

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	FString GetInteractableName() override;

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	FOnInteractionFinished& OnInteractionFinished() override { return OnInteractionFinishedDelegate; }

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	USkeletalMeshComponent* BodyMesh;
};
