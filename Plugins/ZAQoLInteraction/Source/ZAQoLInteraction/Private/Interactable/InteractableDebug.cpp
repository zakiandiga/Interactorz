// Copyright Zaki Agraraharja. All Rights Reserved.


#include "Interactable/InteractableDebug.h"

// Sets default values
AInteractableDebug::AInteractableDebug()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInteractableDebug::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableDebug::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AInteractableDebug::CanInteract_Implementation(const AActor* InteractingActor)
{
	return true;
}

void AInteractableDebug::Interact_Implementation(AActor* InteractingActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Interact with %s"), *InteractingActor->GetName())
}

FString AInteractableDebug::GetInteractableName_Implementation()
{
	return FString("InteractableDebug");
}


