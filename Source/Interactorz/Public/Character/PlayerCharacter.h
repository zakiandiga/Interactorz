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
class UInteractionHandler;
class IInteractable;
class UWIPlayerOverlay;
class UAnimMontage;
class UZAQInteractionHandler;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractableTraced, FName, InteractableName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractableGone);
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

private:	
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UWIPlayerOverlay* PlayerOverlay;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	USphereComponent* InteractableCollider;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "ControllerProperties")
	float RotationRate = 400.f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "ControllerProperties")
	float ZoomRate = 100.f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "ControllerProperties")
	float ZoomInterp = 10.f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "ControllerProperties")
	float DefaultCameraZoom = 140.f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "ControllerProperties")
	float MinCameraZoom = 100.f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "ControllerProperties")
	float MaxCameraZoom = 700.f;

	float DesiredArmLength = 0.f;
	bool bIsCameraZooming = false;

	UPROPERTY(EditAnywhere, meta = (AllowAPrivateAccess = "true"), Category = "Inventory")
	UInventory* PlayerInventory;

	UPROPERTY(VisibleAnywhere, Category = "Player Interaction")
	EPlayerControlStates PlayerControlState = EPlayerControlStates::EPC_OnCharacter;

	UPROPERTY(VisibleAnywhere, Category = "Player Interaction")
	UInteractionHandler* InteractionHandler = nullptr;

	//TESTING
	UPROPERTY(VisibleAnywhere, Category = "Player Interaction")
	UZAQInteractionHandler* ZInteractionHandler = nullptr;

	UPROPERTY()
	AActor* CurrentInteractableActor = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Player Interaction")
	bool bIsLineTracingForInteractable = false;

	UPROPERTY(VisibleAnywhere, Category = "Player Interaction")
	float InteractLineTraceLength = 500.f;

	bool bIsJumping = false;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Animation")
	UAnimMontage* JumpMontage;

	void ToggleMenu();
	void TracingForInteractable();
	void AssignInteractable(AActor* InteractableToAssign);
	void ClearInteractable();
	void FaceInteractable();

	UFUNCTION()
	void StopInteraction();

	void MoveForward(float Value);
	void MoveSide(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void Action01();
	virtual void Jump() override;
	void CameraZoom(float Value);
	void MoveBoomArm(float TargetArmLength, float DeltaTime);

	void TryPlayJumpMontage();

public:

	UFUNCTION(BlueprintPure, Category = "Inventory")
	UInventory* GetInventory() const override { return PlayerInventory; }

	UFUNCTION()
	void OnItemTransferSuccess() override;

	UFUNCTION()
	void OnItemTransferFailed() override;

	UFUNCTION(BlueprintCallable, Category = "MoveStates")
	void SetControlToPlayerCharacter();

	UFUNCTION(BlueprintPure, Category = "Move States")
	FORCEINLINE EPlayerControlStates GetPlayerMoveStates() const { return PlayerControlState; }

	UFUNCTION(BlueprintCallable, Category = "Move States")
	FORCEINLINE void SetPlayerMoveState(EPlayerControlStates StateToSet = EPlayerControlStates::EPC_OnCharacter) { PlayerControlState = StateToSet; }

	UFUNCTION(BlueprintPure, Category = "Jumping")
	FORCEINLINE bool GetIsCurrentlyJumping() { return bIsJumping; }

	UFUNCTION(Category = "Jumping")
	FORCEINLINE void SetIsJumping(bool SetJumping) { bIsJumping = SetJumping; }

	UPROPERTY(BlueprintAssignable)
	FOnInteractableTraced OnInteractableFound;

	UPROPERTY(BlueprintAssignable)
	FOnInteractableGone OnInteractableGone;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerOpeningMenu OnPlayerOpeningMenu;

};
