// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InGameHUD.generated.h"

class UPlayerOverlay;
class UInGameMenu;
class APlayerCharacter;
class UUserWidget;
UCLASS()
class INTERACTORZ_API AInGameHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UInGameMenu> InGameMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UPlayerOverlay> PlayerOverlayClass;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	APlayerCharacter* HUDOwner;

	UPROPERTY(VisibleAnywhere, Category = "Controller")
	APlayerController* PlayerController;

	UPROPERTY()
	UPlayerOverlay* PlayerOverlay;

	UPROPERTY()
	UInGameMenu* InGameMenu;

	UFUNCTION()
	void DisplayInteractableInfo(FString InteractableName);

	UFUNCTION()
	void HideInteractableInfo(FString InteractableName);

	UFUNCTION()
	void OpenMenu(bool bIsOpening);
	
};
