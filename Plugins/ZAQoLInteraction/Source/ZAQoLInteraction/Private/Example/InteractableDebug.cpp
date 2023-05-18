// Copyright Zaki Agraraharja. All Rights Reserved.

#include "Example/InteractableDebug.h"
#include "Components/Interaction/ZAQInteractable.h"

AInteractableDebug::AInteractableDebug()
{
	PrimaryActorTick.bCanEverTick = true;

	Interactable = CreateDefaultSubobject<UZAQInteractable>(TEXT("Interactable"));
}

void AInteractableDebug::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractableDebug::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



