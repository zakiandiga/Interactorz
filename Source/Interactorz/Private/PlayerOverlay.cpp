// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerOverlay.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"

void UPlayerOverlay::SetInteractableInfoPanelVisible(FString InteractableNameToSet)
{
	InteractableInfoText->SetText(FText::FromString(InteractableNameToSet));
	InteractableInfoPanel->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UPlayerOverlay::SetInteractableInfoPanelHidden(FString InteractableNameToRemove)
{
	InteractableInfoText->SetText(FText());
	InteractableInfoPanel->SetVisibility(ESlateVisibility::Hidden);
}
