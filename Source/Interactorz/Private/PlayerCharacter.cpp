// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/PlayerOverlay.h"
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
	InteractableCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Interactable Collider"));

	CameraBoom->SetupAttachment(GetRootComponent());
	PlayerCamera->SetupAttachment(CameraBoom);
	InteractableCollider->SetupAttachment(GetRootComponent());

	CameraBoom->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, RotationRate, 0);

	InteractableCollider->SetGenerateOverlapEvents(true);

	InteractableCollider->IgnoreActorWhenMoving(this, true);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
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
		
	if (bIsLineTracingForInteractable)
	{
		TracingForInteractable();
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &APlayerCharacter::MoveSide);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Action01"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Action01);
	PlayerInputComponent->BindAction(TEXT("Menu"), EInputEvent::IE_Pressed, this, &APlayerCharacter::ToggleMenu);
}

void APlayerCharacter::Jump()
{
	if (Controller == nullptr) return;
	if (PlayerControlState != EPlayerControlStates::EPC_OnCharacter) return;

	Super::Jump();
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

	float CurrentTimeDilation = UGameplayStatics::GetGlobalTimeDilation(this);
	UE_LOG(LogTemp, Warning, TEXT("current global time dilation = %f"), CurrentTimeDilation);
	switch (PlayerControlState)
	{
	case EPlayerControlStates::EPC_OnMenu:
		UGameplayStatics::SetGlobalTimeDilation(this, 1.f);
		OnPlayerOpeningMenu.Broadcast(false);
		PlayerControlState = EPlayerControlStates::EPC_OnCharacter;
		break;
	case EPlayerControlStates::EPC_OnCharacter:
		UGameplayStatics::SetGlobalTimeDilation(this, 0.f);
		OnPlayerOpeningMenu.Broadcast(true);
		PlayerControlState = EPlayerControlStates::EPC_OnMenu;
		break;
	case EPlayerControlStates::EPC_Interacting:
		//to be implemented
		break;
	default:
		break;
	}
}

void APlayerCharacter::TracingForInteractable()
{
	FVector Start = PlayerCamera->GetComponentLocation() + (PlayerCamera->GetForwardVector() * CameraBoom->TargetArmLength);
	FVector End = Start + (PlayerCamera->GetForwardVector() * InteractLineTraceLength);
	FHitResult CurrentHitResult;
	FCollisionQueryParams LineTraceParams;
	LineTraceParams.AddIgnoredActor(this);

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

	PlayerControlState = EPlayerControlStates::EPC_OnCharacter;
}

void APlayerCharacter::OnItemTransferFailed()
{
	//Display inventory is full warning

	PlayerControlState = EPlayerControlStates::EPC_OnCharacter;
}




