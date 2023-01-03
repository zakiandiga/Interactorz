// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WIMainMenu.generated.h"

UCLASS()
class INTERACTORZ_API UWIMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
private:
	void NativeConstruct() override;

	UFUNCTION()
	void NativeDestruct()override;

};
