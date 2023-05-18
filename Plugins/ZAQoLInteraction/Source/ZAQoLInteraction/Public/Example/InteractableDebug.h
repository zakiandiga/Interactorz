// Copyright Zaki Agraraharja. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableDebug.generated.h"

class UZAQInteractable;

UCLASS(Blueprintable)
class ZAQOLINTERACTION_API AInteractableDebug : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractableDebug();

private:
	UZAQInteractable* Interactable;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


};
