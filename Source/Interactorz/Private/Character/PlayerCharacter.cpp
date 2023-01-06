// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/PlayerOverlay.h"
#include "Inventory.h"
#include "DA_ItemData.h"
#include "Interfaces/Interactable.h"
#include "Animation/AnimMontage.h"
#include "DebugHelpers/DebugMacros.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	PlayerInventory = CreateDefaultSubobject<UInventory>(TEXT("Player Inventory"));
	PlayerOverlay = CreateDefaultSubobject<UPlayerOverlay>(TEXT("Player Overlay"));
	InteractableCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Interactable Collider"));

	CameraBoom->SetupAttachment(GetRootComponent());
	PlayerCamera->SetupAttachment(CameraBoom);
	InteractableCollider->SetupAttachment(GetRootComponent());

	CameraBoom->TargetArmLength = DefaultCameraZoom;
	CameraBoom->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, RotationRate, 0);

	InteractableCollider->SetGenerateOverlapEvents(true);

	InteractableCollider->IgnoreActorWhenMoving(this, true);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	FString Message = Controller->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Character: %s"), *Message);

	InteractLineTraceLength = InteractableCollider->GetScaledSphereRadius();

	InteractableCollider->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::BeginOverlapDelegate);
	InteractableCollider->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::EndOverlapDelegate);

	TSet<AActor*> CurrentlyOverlappingActors;
	InteractableCollider->GetOverlappingActors(CurrentlyOverlappingActors);

	if (CurrentlyOverlappingActors.Num() <= 0) return;
	bIsLineTracingForInteractable = true;
}

void APlayerCharacter::BeginOverlapDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this) return;
	if (bIsLineTracingForInteractable) return;

	bIsLineTracingForInteractable = true;
}

void APlayerCharacter::EndOverlapDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!bIsLineTracingForInteractable) return;

	TSet<AActor*> CurrentlyOverlappingActors; 
	InteractableCollider->GetOverlappingActors(CurrentlyOverlappingActors);

	if (CurrentlyOverlappingActors.Num() > 0) return;

	ClearInteractable();
	bIsLineTracingForInteractable = false;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
	if (PlayerControlState == EPlayerControlStates::EPC_OnCharacter && !InputEnabled())
	{
		EnableInput(Cast<APlayerController>(Controller));
	}

	if (bIsLineTracingForInteractable)
	{
		TracingForInteractable();
	}

	if (!GetMovementComponent()->IsFalling() && GetIsCurrentlyJumping())
	{
		SetIsJumping(false);
	}

	if (bIsCameraZooming)
	{
		MoveBoomArm(DesiredArmLength, DeltaTime);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	FInputAxisBinding& Forward = PlayerInputComponent->BindAxis(TEXT("Forward"), this, &APlayerCharacter::MoveForward);
	FInputAxisBinding& Right = PlayerInputComponent->BindAxis(TEXT("Right"), this, &APlayerCharacter::MoveSide);
	FInputAxisBinding& LookRight = PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APlayerCharacter::Turn);
	FInputAxisBinding& LookUp = PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	FInputAxisBinding& Zoom = PlayerInputComponent->BindAxis(TEXT("Zoom"), this, &APlayerCharacter::CameraZoom);

	FInputActionBinding& Jump = PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Jump);
	FInputActionBinding& Action01 = PlayerInputComponent->BindAction(TEXT("Action01"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Action01);
	FInputActionBinding& Menu = PlayerInputComponent->BindAction(TEXT("Menu"), EInputEvent::IE_Pressed, this, &APlayerCharacter::ToggleMenu);
	
	Forward.bConsumeInput = false;
	Right.bConsumeInput = false;
	LookRight.bConsumeInput = false;
	LookUp.bConsumeInput = false;
	Zoom.bConsumeInput = false;
	Menu.bConsumeInput = false;
}

void APlayerCharacter::Jump()
{
	if (Controller == nullptr) return;
	if (PlayerControlState != EPlayerControlStates::EPC_OnCharacter) return;

	SetIsJumping(true);
	Super::Jump();
}

void APlayerCharacter::CameraZoom(float Value)
{
	if (Controller == nullptr) return;
	if (Value == 0) return;
	if (PlayerControlState != EPlayerControlStates::EPC_OnCharacter) return;

	DesiredArmLength = CameraBoom->TargetArmLength + (Value * ZoomRate);
	bIsCameraZooming = true;
}

void APlayerCharacter::MoveBoomArm(float ToArmLength, float DeltaTime)
{
	CameraBoom->TargetArmLength = FMath::FInterpTo(CameraBoom->TargetArmLength, DesiredArmLength, DeltaTime, ZoomInterp);
	CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength, MinCameraZoom, MaxCameraZoom);

	if (CameraBoom->TargetArmLength >= MaxCameraZoom
		|| CameraBoom->TargetArmLength <= MinCameraZoom 
		|| FMath::IsNearlyEqual(CameraBoom->TargetArmLength, DesiredArmLength, 0.1f))
	{
		bIsCameraZooming = false;
	}
}


void APlayerCharacter::TryPlayJumpMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if (AnimInstance == nullptr && JumpMontage == nullptr) return;

	AnimInstance->Montage_Play(JumpMontage);
	FName SectionName = UKismetMathLibrary::VSizeXY(GetCharacterMovement()->Velocity) > 0 ? FName("JumpRun") : FName("JumpDefault");
	AnimInstance->Montage_JumpToSection(SectionName, JumpMontage);
}

void APlayerCharacter::MoveForward(float Value)
{
	if (Controller == nullptr) return;
	if (Value == 0) return;
	if (PlayerControlState != EPlayerControlStates::EPC_OnCharacter) return;

	const FRotator ControllerRotation = GetControlRotation();
	const FRotator YawRotation(0, ControllerRotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, Value);
}

void APlayerCharacter::MoveSide(float Value)
{
	if (Controller == nullptr) return;
	if (Value == 0) return;
	if (PlayerControlState != EPlayerControlStates::EPC_OnCharacter) return;

	const FRotator ControllerRotation = GetControlRotation();
	const FRotator YawRotation(0, ControllerRotation.Yaw, 0);

	const FVector SideDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(SideDirection, Value);
}

void APlayerCharacter::Turn(float Value)
{
	if (Controller == nullptr) return;
	if (Value == 0) return;
	if (PlayerControlState != EPlayerControlStates::EPC_OnCharacter) return;

	AddControllerYawInput(Value);
}

void APlayerCharacter::LookUp(float Value)
{
	if (Controller == nullptr) return;
	if (Value == 0) return;
	if (PlayerControlState != EPlayerControlStates::EPC_OnCharacter) return;

	AddControllerPitchInput(Value);
}

void APlayerCharacter::Action01()
{
	if (Controller == nullptr) return;
	if (PlayerControlState != EPlayerControlStates::EPC_OnCharacter) return;

	if (CurrentInteractable == nullptr) return;

	//start interacting animation, on selected montage, change PlayerControlState back to OnCharacter

	PlayerControlState = EPlayerControlStates::EPC_Interacting;
	CurrentInteractable->Interact(Cast<AActor>(this));
	FaceInteractable();
}

void APlayerCharacter::ToggleMenu()
{
	if (Controller == nullptr) return;
	if (PlayerControlState == EPlayerControlStates::EPC_Interacting) return;

	switch (PlayerControlState)
	{
	case EPlayerControlStates::EPC_OnMenu:
		//UGameplayStatics::SetGlobalTimeDilation(this, 1.f);
		OnPlayerOpeningMenu.Broadcast(false);
		Controller->SetIgnoreLookInput(false);
		Controller->SetIgnoreMoveInput(false);
		EnableInput(Cast<APlayerController>(Controller));
		PlayerControlState = EPlayerControlStates::EPC_OnCharacter;
		break;
	case EPlayerControlStates::EPC_OnCharacter:
		//UGameplayStatics::SetGlobalTimeDilation(this, 0.f);
		OnPlayerOpeningMenu.Broadcast(true);
		Controller->SetIgnoreLookInput(true);
		Controller->SetIgnoreMoveInput(true);
		DisableInput(Cast<APlayerController>(Controller));
		PlayerControlState = EPlayerControlStates::EPC_OnMenu;
		break;
	case EPlayerControlStates::EPC_Interacting:
		//to be implemented
		break;
	default:
		break;
	}
}

void APlayerCharacter::SetControlToPlayerCharacter()
{
	Controller->SetIgnoreLookInput(false);
	Controller->SetIgnoreMoveInput(false);
	EnableInput(Cast<APlayerController>(Controller));
	PlayerControlState = EPlayerControlStates::EPC_OnCharacter;
}

void APlayerCharacter::TracingForInteractable()
{
	FVector Start = PlayerCamera->GetComponentLocation() + (PlayerCamera->GetForwardVector() * CameraBoom->TargetArmLength);
	FVector End = Start + (PlayerCamera->GetForwardVector() * InteractLineTraceLength);
	FHitResult CurrentHitResult;
	FCollisionQueryParams LineTraceParams;
	LineTraceParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(CurrentHitResult, Start, End, ECollisionChannel::ECC_Visibility, LineTraceParams);
	DRAW_LINE_Tick(Start, End, FColor::Green);

	IInteractable* HitInteractable = Cast<IInteractable>(CurrentHitResult.GetActor());

	if (HitInteractable == nullptr)
	{
		ClearInteractable();
		return;
	}

	AssignInteractable(HitInteractable);	
}

void APlayerCharacter::AssignInteractable(IInteractable* InteractableToAssign)
{
	if (InteractableToAssign == CurrentInteractable) return;

	ClearInteractable();
	CurrentInteractable = InteractableToAssign;	
	OnInteractableFound.Broadcast(CurrentInteractable->GetInteractableName());
}

void APlayerCharacter::ClearInteractable()
{
	if (CurrentInteractable == nullptr) return;

	OnInteractableGone.Broadcast(CurrentInteractable->GetInteractableName());
	CurrentInteractable = nullptr;
}

void APlayerCharacter::FaceInteractable()
{
	if (CurrentInteractable == nullptr) return;

	FVector TargetLook = Cast<AActor>(CurrentInteractable)->GetActorLocation() - GetActorLocation();

	FRotator LookRotation = FRotator::ZeroRotator;
	LookRotation.Yaw = TargetLook.Rotation().Yaw;

	FRotator CurrentRotation = GetViewRotation();

	SetActorRotation(LookRotation);
}

void APlayerCharacter::OnItemTransferSuccess()
{
	//Display item retrieved message
	//finishinginteraction()
	PlayerControlState = EPlayerControlStates::EPC_OnCharacter;
}

void APlayerCharacter::OnItemTransferFailed()
{
	//Display inventory is full warning
	//finishinginteraction()
	PlayerControlState = EPlayerControlStates::EPC_OnCharacter;
}