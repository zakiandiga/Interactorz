// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBase.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"

AInteractableBase::AInteractableBase()
{
	PrimaryActorTick.bCanEverTick = true;

	//InteractableCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Interact Collider"));	

	//InteractableCollider->SetSphereRadius(InteractRange, true);
	//InteractableCollider->SetCollisionProfileName("InteractableTrigger");
}

void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();
	
	//InteractableCollider->OnComponentBeginOverlap.AddDynamic(this, &AInteractableBase::BeginOverlapDelegate);
	//InteractableCollider->OnComponentEndOverlap.AddDynamic(this, &AInteractableBase::EndOverlapDelegate);	
}

/*
void AInteractableBase::ToggleIconVisible(bool bIsSetToVisible)
{
	//set interact icon widget visible/hidden
}

void AInteractableBase::BeginOverlapDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ToggleIconVisible(true);	
	CurrentInteractablePlayer = OtherActor;
}

void AInteractableBase::EndOverlapDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ToggleIconVisible(false);
	CurrentInteractablePlayer = nullptr;
}
*/

