// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InteractorzPlayerController.generated.h"

class APlayerCharacter;
UCLASS()
class INTERACTORZ_API AInteractorzPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AInteractorzPlayerController();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void UINavigateVertical(float Value);

	UFUNCTION(BlueprintCallable)
	void UINavigateHorizontal(float Value);

	UFUNCTION(BlueprintCallable)
	void Confirm();

	UFUNCTION(BlueprintCallable)
	void Cancel();

	APlayerCharacter* PossessedPawn;
};
