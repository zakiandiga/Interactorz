// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameHUD.h"
#include "Components/WidgetSwitcher.h"
#include "UI/PlayerOverlay.h"
#include "UI/InGameMenu.h"
#include "PlayerCharacter.h"

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetFirstPlayerController();
	PlayerController = GetWorld()->GetFirstPlayerController();
	HUDOwner = Cast<APlayerCharacter>(PlayerController->GetPawn());
	
	if (PlayerController == nullptr || PlayerOverlayClass == nullptr) return;

	PlayerOverlay = CreateWidget<UPlayerOverlay>(PlayerController, PlayerOverlayClass);
	PlayerOverlay->AddToViewport();
	PlayerOverlay->SetInteractableInfoPanelHidden(FString());

	InGameMenu = CreateWidget<UInGameMenu>(PlayerController, InGameMenuClass);
	InGameMenu->AddToViewport();
	InGameMenu->SetMainPanelHidden();

	PlayerController->SetShowMouseCursor(false);

	if (HUDOwner == nullptr) return;

	InGameMenu->SetOwnerInventory(HUDOwner->GetActorInventory());

	HUDOwner->OnInteractableFound.AddDynamic(this, &AInGameHUD::DisplayInteractableInfo);
	HUDOwner->OnInteractableGone.AddDynamic(this, &AInGameHUD::HideInteractableInfo);

	HUDOwner->OnPlayerOpeningMenu.AddDynamic(this, &AInGameHUD::OpenMenu);
}

void AInGameHUD::DisplayInteractableInfo(FString InteractableName)
{
	UE_LOG(LogTemp, Warning, TEXT("Displaying interactrable: %s"), *InteractableName);
	PlayerOverlay->SetInteractableInfoPanelVisible(InteractableName);
}

void AInGameHUD::HideInteractableInfo(FString InteractableName)
{
	PlayerOverlay->SetInteractableInfoPanelHidden(InteractableName);
}

void AInGameHUD::OpenMenu(bool bIsOpening)
{
	if (PlayerController == nullptr) return;
	
	if (!bIsOpening)
	{
		//PlayerController->SetInputMode(FInputModeUIOnly());
		PlayerController->SetShowMouseCursor(false);
		InGameMenu->ClearInventoryList();
		InGameMenu->SetMainPanelHidden();
		return;
	}

	//PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(true);
	InGameMenu->DisplayInventoryList();
	InGameMenu->SetMainPanelVisible();
}
