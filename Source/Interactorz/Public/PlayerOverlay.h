// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerOverlay.generated.h"

//This is a part of HUD, Attached to the screen, not the player.

class UCanvasPanel;
class UTextBlock;
UCLASS()
class INTERACTORZ_API UPlayerOverlay : public UUserWidget
{
	GENERATED_BODY()	


public:

	void SetInteractableInfoPanelVisible(FString InteractableNameToSet);
	void SetInteractableInfoPanelHidden(FString InteractableNameToRemove);

private:

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* InteractableInfoPanel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* InteractableInfoText;
};
