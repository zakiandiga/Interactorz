// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WIPlayerOverlay.generated.h"

class UCanvasPanel;
class UTextBlock;
UCLASS()
class INTERACTORZ_API UWIPlayerOverlay : public UUserWidget
{
	GENERATED_BODY()	

public:

	UFUNCTION()
	void SetInteractableInfoPanelVisible(FString InteractableNameToSet);

	UFUNCTION()
	void SetInteractableInfoPanelHidden(FString InteractableNameToRemove);

private:

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* InteractableInfoPanel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* InteractableInfoText;
};
