// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameMenu.generated.h"

class UCanvasPanel;
UCLASS()
class INTERACTORZ_API UInGameMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetMainPanelVisible();
	void SetMainPanelHidden();

private:
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* MainPanel;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* InventoryPanel;
};
