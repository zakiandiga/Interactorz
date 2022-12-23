// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUD.h"
#include "PlayerOverlay.h"
#include "PlayerCharacter.h"

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	
	if (Controller == nullptr || PlayerOverlayClass == nullptr) return;

	PlayerOverlay = CreateWidget<UPlayerOverlay>(Controller, PlayerOverlayClass);
	PlayerOverlay->AddToViewport();
	PlayerOverlay->SetInteractableInfoPanelHidden(FString());

	APlayerCharacter* Player = Cast<APlayerCharacter>(Controller->GetPawn());
	if (Player == nullptr) return;

	Player->OnInteractableFound.AddDynamic(this, &AInGameHUD::DisplayInteractableInfo);
	Player->OnInteractableGone.AddDynamic(this, &AInGameHUD::HideInteractableInfo);
}

void AInGameHUD::DisplayInteractableInfo(FString InteractableName)
{
	PlayerOverlay->SetInteractableInfoPanelVisible(InteractableName);
}

void AInGameHUD::HideInteractableInfo(FString InteractableName)
{
	PlayerOverlay->SetInteractableInfoPanelHidden(InteractableName);
}
