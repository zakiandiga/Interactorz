// Copyright Zaki Agraraharja. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ZAQIInteractable.h"
#include "InteractableDebug.generated.h"

class ZAQIInteractable;
UCLASS()
class ZAQOLINTERACTION_API AInteractableDebug : public AActor, public IZAQIInteractable
{
	GENERATED_BODY()
	
public:	
	AInteractableDebug();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	bool CanInteract_Implementation(const AActor* InteractingActor);
	void Interact_Implementation(AActor* InteractingActor);
	FString GetInteractableName_Implementation();	

};
