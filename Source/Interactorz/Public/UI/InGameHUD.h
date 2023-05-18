// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InGameHUD.generated.h"

class UWIPlayerOverlay;
class UWIInGameMenu;
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
	TSubclassOf<UWIInGameMenu> InGameMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UWIPlayerOverlay> PlayerOverlayClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UWIInGameMenu> StorageMenuClass;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	APlayerCharacter* HUDOwner;

	UPROPERTY(VisibleAnywhere, Category = "Controller")
	APlayerController* PlayerController;

	UPROPERTY()
	UWIPlayerOverlay* PlayerOverlay;

	UPROPERTY()
	UWIInGameMenu* InGameMenu;

	UPROPERTY()
	UWIInGameMenu* StorageMenu;

	void CreateMainUI();

	void BindPlayerActions();
	
	UFUNCTION()
	void DisplayInteractableName(FName InteractableName);

	UFUNCTION()
	void HideInteractableInfo();

	UFUNCTION()
	void OpenMenu(bool bIsOpening);

public:
	UFUNCTION(BlueprintCallable, Category = "UI | Navigation")
	void OpenMenuFromBP(bool bIsOpeningMenu);

	UFUNCTION(BlueprintCallable)
	void OpenStorageMenu(bool IsOpening);

	
};
