// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WIPlayerOverlay.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"

void UWIPlayerOverlay::SetInteractableInfoPanelVisible(FString InteractableNameToSet)
{
	InteractableInfoText->SetText(FText::FromString(InteractableNameToSet));
	InteractableInfoPanel->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UWIPlayerOverlay::SetInteractableInfoPanelHidden(FString InteractableNameToRemove)
{
	InteractableInfoText->SetText(FText());
	InteractableInfoPanel->SetVisibility(ESlateVisibility::Hidden);
}
