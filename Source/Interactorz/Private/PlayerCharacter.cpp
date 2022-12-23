// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "PlayerOverlay.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Inventory.h"
#include "Interfaces/Interactable.h"
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

	CameraBoom->SetupAttachment(GetRootComponent());
	PlayerCamera->SetupAttachment(CameraBoom);

	CameraBoom->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, RotationRate, 0);

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::BeginOverlapDelegate);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::EndOverlapDelegate);

	TSet<AActor*> CurrentlyOverlappingActors;
	GetOverlappingActors(CurrentlyOverlappingActors);

	if (CurrentlyOverlappingActors.Num() <= 0) return;

	bIsLineTracingForInteractable = true;
	
}

void APlayerCharacter::BeginOverlapDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//start linesweep
	if (bIsLineTracingForInteractable) return;

	bIsLineTracingForInteractable = true;
	UE_LOG(LogTemp, Warning, TEXT("LineTracing for Interactable currently ON"));
}

void APlayerCharacter::EndOverlapDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!bIsLineTracingForInteractable) return;

	TSet<AActor*> CurrentlyOverlappingActors; 
	GetOverlappingActors(CurrentlyOverlappingActors);
	
	if (CurrentlyOverlappingActors.Num() > 0) return;

	bIsLineTracingForInteractable = false;
	UE_LOG(LogTemp, Warning, TEXT("LineTracing for Interactable currently OFF"));

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsLineTracingForInteractable)
	{
		if (CurrentInteractable == nullptr) return;

		OnInteractableGone.Broadcast(CurrentInteractable->GetInteractableName());
		CurrentInteractable = nullptr;
		return;
	}

	TracingForInteractable();	
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &APlayerCharacter::MoveSide);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Action01"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Action01);

}

void APlayerCharacter::MoveForward(float Value)
{
	if (Controller == nullptr) return;
	if (Value == 0) return;

	const FRotator ControllerRotation = GetControlRotation();
	const FRotator YawRotation(0, ControllerRotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, Value);
}

void APlayerCharacter::MoveSide(float Value)
{
	if (Controller == nullptr) return;
	if (Value == 0) return;

	const FRotator ControllerRotation = GetControlRotation();
	const FRotator YawRotation(0, ControllerRotation.Yaw, 0);

	const FVector SideDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(SideDirection, Value);
}

void APlayerCharacter::Turn(float Value)
{
	if (Controller == nullptr) return;
	if (Value == 0) return;

	AddControllerYawInput(Value);
}

void APlayerCharacter::LookUp(float Value)
{
	if (Controller == nullptr) return;
	if (Value == 0) return;

	AddControllerPitchInput(Value);
}

void APlayerCharacter::Action01()
{
	if (CurrentInteractable == nullptr) return;
	if (!CurrentInteractable->CanInteract(Cast<AActor>(this))) return;

	//start interacting animation, on selected montage, change PlayerControlState back to OnCharacter
	
	//Temporary interact
	PlayerControlState = EPlayerControlStates::EPC_Interacting;
	CurrentInteractable->Interact();

	PlayerControlState = EPlayerControlStates::EPC_OnCharacter;
}

void APlayerCharacter::TracingForInteractable()
{

	FVector Start = CameraBoom->GetComponentLocation();
	FVector End = Start + (PlayerCamera->GetForwardVector() * InteractLineTraceLength);
	FHitResult CurrentHitResult;
	FCollisionQueryParams LineTraceParams;
	LineTraceParams.AddIgnoredActor(this);
	
	DRAW_LINE_Tick(Start, End, FColor::Cyan);
	GetWorld()->LineTraceSingleByChannel(CurrentHitResult, Start, End, ECollisionChannel::ECC_Visibility, LineTraceParams);

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


	///Current bug:
	//if a pickup item spawned at where the player is inside the overlap range, it doesn't register the player as current interactable player

}

void APlayerCharacter::ClearInteractable()
{
	if (CurrentInteractable == nullptr) return;

	OnInteractableGone.Broadcast(CurrentInteractable->GetInteractableName());
	CurrentInteractable = nullptr;
}




