// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractorzPlayerController.h"
#include "PlayerCharacter.h"
#include "GameFramework/PlayerController.h"

AInteractorzPlayerController::AInteractorzPlayerController()
{

}

void AInteractorzPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PossessedPawn = Cast<APlayerCharacter>(GetPawn());
}

void AInteractorzPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent->BindAxis("Forward", this, &AInteractorzPlayerController::UINavigateVertical);
	//InputComponent->BindAxis("Right", this, &AInteractorzPlayerController::UINavigateHorizontal);
	//InputComponent->BindAction("Confirm", IE_Pressed, this, &AInteractorzPlayerController::Confirm);
	//InputComponent->BindAction("Cancel", IE_Pressed, this, &AInteractorzPlayerController::Cancel);

}

void AInteractorzPlayerController::Tick(float DeltaTime)
{
}

void AInteractorzPlayerController::UINavigateVertical(float Value)
{
	if (Value == 0) return;

	if (PossessedPawn->GetPlayerMoveStates() == EPlayerControlStates::EPC_OnCharacter)
	{
		//PossessedPawn->MoveForward(Value);
	}

	else if (PossessedPawn->GetPlayerMoveStates() == EPlayerControlStates::EPC_OnMenu)
	{
		UE_LOG(LogTemp, Warning, TEXT("NavigateVertical! %f"), Value);

	}
}

void AInteractorzPlayerController::UINavigateHorizontal(float Value)
{
	if (Value == 0) return;

	UE_LOG(LogTemp, Warning, TEXT("NavigateHorizontal!"));
}

void AInteractorzPlayerController::Confirm()
{
	UE_LOG(LogTemp, Warning, TEXT("Confirm Pressed!"));
}

void AInteractorzPlayerController::Cancel()
{
	UE_LOG(LogTemp, Warning, TEXT("Cancel Pressed!"));
}
