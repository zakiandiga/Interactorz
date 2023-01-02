// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IUISwitcherListener.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UIUISwitcherListener : public UInterface
{
	GENERATED_BODY()
};

class INTERACTORZ_API IIUISwitcherListener
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UI | Navigation")
	void OnPageOpened(class UWidget* OpenedWidget);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UI | Navigation")
	void OnPageClosed(class UWidget* ClosedWidget);

};
