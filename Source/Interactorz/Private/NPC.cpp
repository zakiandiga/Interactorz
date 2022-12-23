// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "Components/SphereComponent.h"

ANPC::ANPC()
{
	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
    
    BodyMesh->SetupAttachment(RootComponent);
    //InteractableCollider->SetupAttachment(BodyMesh);

}

void ANPC::BeginPlay()
{
    //Super::BeginPlay();
}

void ANPC::Tick(float DeltaTime)
{
    //Super::Tick(DeltaTime);
}

bool ANPC::CanInteract(const AActor* InteractingActor)
{
    return true; // InteractingActor == GetCurrentInteractableActor();
}

void ANPC::Interact(AActor* InteractingActor)
{
    //Start dialogue interface
}

FString ANPC::GetInteractableName()
{
    return FString();
}

