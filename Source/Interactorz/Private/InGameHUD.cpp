// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUD.h"
#include "PlayerOverlay.h"
#include "UI/InGameMenu.h"
#include "PlayerCharacter.h"

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	HUDOwner = Cast<APlayerCharacter>(Controller->GetPawn());
	
	if (Controller == nullptr || PlayerOverlayClass == nullptr) return;

	PlayerOverlay = CreateWidget<UPlayerOverlay>(Controller, PlayerOverlayClass);
	PlayerOverlay->AddToViewport();
	PlayerOverlay->SetInteractableInfoPanelHidden(FString());

	InGameMenu = CreateWidget<UInGameMenu>(Controller, InGameMenuClass);
	InGameMenu->AddToViewport();
	InGameMenu->SetMainPanelHidden();

	if (HUDOwner == nullptr) return;

	InGameMenu->SetOwnerInventory(HUDOwner->GetActorInventory());

	HUDOwner->OnInteractableFound.AddDynamic(this, &AInGameHUD::DisplayInteractableInfo);
	HUDOwner->OnInteractableGone.AddDynamic(this, &AInGameHUD::HideInteractableInfo);

	HUDOwner->OnPlayerOpeningMenu.AddDynamic(this, &AInGameHUD::OpenMenu);
}

void AInGameHUD::DisplayInteractableInfo(FString InteractableName)
{
	PlayerOverlay->SetInteractableInfoPanelVisible(InteractableName);
}

void AInGameHUD::HideInteractableInfo(FString InteractableName)
{
	PlayerOverlay->SetInteractableInfoPanelHidden(InteractableName);
}

void AInGameHUD::OpenMenu(bool bIsOpening)
{
	if (!bIsOpening)
	{
		InGameMenu->ClearInventoryList();
		return;
	}

	InGameMenu->DisplayInventoryList();
	InGameMenu->SetMainPanelVisible();
}
