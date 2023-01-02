// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetSwitcher.h"
#include "WIWidgetSwitcher.generated.h"

UCLASS()
class INTERACTORZ_API UWIWidgetSwitcher : public UWidgetSwitcher
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI | Navigation")
	void OnPanelVisible(bool IsVisible);

	UFUNCTION(BlueprintCallable, Category = "UI | Navigation")
	void PageChange(float Value);

	UFUNCTION()
	void HandlePageClosing(UWidget* PreviousWidget);

	UFUNCTION()
	void HandlePageOpening(UWidget* NextWidget);

	bool IsPageCycling(int32 NextPageIndex);

	int32 CyclePage(int32 NextPageIndex) const;

};
