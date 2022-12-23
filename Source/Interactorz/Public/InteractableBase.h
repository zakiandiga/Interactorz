// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableBase.generated.h"

class USphereComponent;
class UPrimitiveComponent;
UCLASS()
class INTERACTORZ_API AInteractableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractableBase();


protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	USphereComponent* InteractableCollider;
	
	UFUNCTION()
	virtual void BeginOverlapDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void EndOverlapDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	
	UPROPERTY(EditAnywhere, Category = "Components")
	float InteractRange = 50.f;

	bool bIsActive = true;
	
	AActor* CurrentInteractablePlayer;

	bool bIsPlayerAssigned = false;

	UFUNCTION()
	void ToggleIconVisible(bool bIsSetToVisible);

public:
	void SetActiveState(bool bIsSetActive);
	FORCEINLINE bool GetActiveState() { return bIsActive; };
	FORCEINLINE AActor* GetCurrentInteractableActor() { return CurrentInteractablePlayer; };

};
