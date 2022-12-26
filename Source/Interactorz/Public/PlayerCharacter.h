// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/InventoryOwner.h"
#include "PlayerStates.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USphereComponent;
class UInventory;
class IInteractable;
class UPlayerOverlay;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractableTraced, FString, InteractableName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerOpeningMenu, bool, bIsOpening); //false = closing
UCLASS()
class INTERACTORZ_API APlayerCharacter : public ACharacter, public IInventoryOwner
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void BeginOverlapDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlapDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;

private:	
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UPlayerOverlay* PlayerOverlay;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	USphereComponent* InteractableCollider;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "ControllerProperties");
	float RotationRate = 400.f;

	UPROPERTY(EditAnywhere, meta = (AllowAPrivateAccess = "true"), Category = "Inventory")
	UInventory* PlayerInventory;

	UPROPERTY(VisibleAnywhere, Category = "Player Interaction")
	EPlayerControlStates PlayerControlState = EPlayerControlStates::EPC_OnCharacter;

	IInteractable* CurrentInteractable = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Player Interaction")
	bool bIsLineTracingForInteractable = false;

	UPROPERTY(VisibleAnywhere, Category = "Player Interaction")
	float InteractLineTraceLength = 500.f;

	void MoveForward(float Value);
	void MoveSide(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void Action01();
	void ToggleMenu();
	void TracingForInteractable();
	void AssignInteractable(IInteractable* InteractableToAssign);
	void ClearInteractable();
	void FaceInteractable();


public:

	virtual void OnItemTransferSuccess() override;
	virtual void OnItemTransferFailed() override;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	FORCEINLINE UInventory* GetActorInventory() const { return PlayerInventory; }

	UFUNCTION(BlueprintPure, Category = "Move States")
	FORCEINLINE EPlayerControlStates GetPlayerMoveStates() const { return PlayerControlState; }

	UFUNCTION(BlueprintCallable, Category = "Move States")
	FORCEINLINE void SetPlayerMoveState(EPlayerControlStates StateToSet = EPlayerControlStates::EPC_OnCharacter) { PlayerControlState = StateToSet; }

	UPROPERTY(BlueprintAssignable)
	FOnInteractableTraced OnInteractableFound;

	UPROPERTY(BlueprintAssignable)
	FOnInteractableTraced OnInteractableGone;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerOpeningMenu OnPlayerOpeningMenu;

};
