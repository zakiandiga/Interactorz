// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameHUD.h"
#include "Components/WidgetSwitcher.h"
#include "UI/WIPlayerOverlay.h"
#include "UI/WIInGameMenu.h"
#include "Character/PlayerCharacter.h"

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetWorld()->GetFirstPlayerController();
	
	if (PlayerController == nullptr || PlayerOverlayClass == nullptr || StorageMenuClass == nullptr) return;

	HUDOwner = Cast<APlayerCharacter>(PlayerController->GetPawn());
	
	if (HUDOwner == nullptr) return;

	CreateMainUI();
	BindPlayerActions();
}

void AInGameHUD::CreateMainUI()
{
	PlayerOverlay = CreateWidget<UWIPlayerOverlay>(PlayerController, PlayerOverlayClass);
	PlayerOverlay->AddToViewport();
	PlayerOverlay->SetInteractableInfoPanelHidden(FString());

	InGameMenu = CreateWidget<UWIInGameMenu>(PlayerController, InGameMenuClass);
	InGameMenu->AddToViewport();
	InGameMenu->SetMainPanelHidden();

	StorageMenu = CreateWidget<UWIInGameMenu>(PlayerController, StorageMenuClass);
	StorageMenu->AddToViewport();
	StorageMenu->SetMainPanelHidden();

	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false); //Should be set somewhere else?	

	InGameMenu->SetOwnerInventory(HUDOwner->GetInventory());
	InGameMenu->OnMenuCreated.Broadcast(InGameMenu);
}

void AInGameHUD::BindPlayerActions()
{
	HUDOwner->OnInteractableFound.AddDynamic(this, &AInGameHUD::DisplayInteractableName);
	HUDOwner->OnInteractableGone.AddDynamic(this, &AInGameHUD::HideInteractableInfo);
	HUDOwner->OnPlayerOpeningMenu.AddDynamic(this, &AInGameHUD::OpenMenu);
}

void AInGameHUD::DisplayInteractableName(FName InteractableName)
{
	//UE_LOG(LogTemp, Warning, TEXT("Displaying interactrable: %s"), *InteractableName);
	PlayerOverlay->SetInteractableInfoPanelVisible(InteractableName.ToString());
}

void AInGameHUD::HideInteractableInfo()
{
	PlayerOverlay->SetInteractableInfoPanelHidden(FString());
}

void AInGameHUD::OpenMenu(bool bIsOpening)
{
	if (PlayerController == nullptr) return;
	
	if (!bIsOpening)
	{
		//PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);
		InGameMenu->SetMainPanelHidden();
		HUDOwner->SetControlToPlayerCharacter();
		return;
	}

	//PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->SetShowMouseCursor(true);
	InGameMenu->SetMainPanelVisible();
}

void AInGameHUD::OpenMenuFromBP(bool bIsOpeningMenu)
{
	OpenMenu(bIsOpeningMenu);
}

void AInGameHUD::OpenStorageMenu(bool IsOpening)
{
	if (PlayerController == nullptr) return;

	if (!IsOpening)
	{
		PlayerController->SetShowMouseCursor(false);
		StorageMenu->SetMainPanelHidden();
		HUDOwner->SetControlToPlayerCharacter();
		return;
	}

	PlayerController->SetShowMouseCursor(true);
	StorageMenu->SetMainPanelVisible();
}

