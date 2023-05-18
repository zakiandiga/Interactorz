// Copyright Zaki Agraraharja. All Rights Reserved.


#include "Components/Interaction/ZAQInteractableCollider.h"
#include "Components/Interaction/ZAQInteractionHandler.h"

UZAQInteractableCollider::UZAQInteractableCollider()
{	
	InitSphereRadius(400.f);
	CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	SetCollisionProfileName("Interactable");
	SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);

	SetGenerateOverlapEvents(true);
	IgnoreActorWhenMoving(GetOwner(), true);
}

void UZAQInteractableCollider::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner() == nullptr) return;

	InteractionHandlerComponent = Cast<UZAQInteractionHandler>(GetOwner()->GetComponentByClass(UZAQInteractionHandler::StaticClass()));
	
	OnComponentBeginOverlap.AddDynamic(this, &UZAQInteractableCollider::BeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UZAQInteractableCollider::EndOverlap);	

	UpdateOverlappingActorsTSet();
}

void UZAQInteractableCollider::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CurrentInteractableActorsInRange.Add(OtherActor);

	OnInteractableEnter.Broadcast();
}

void UZAQInteractableCollider::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CurrentInteractableActorsInRange.Remove(OtherActor);

	if (HasOverlappingActors()) return;

	OnInteractableExit.Broadcast();
}

bool UZAQInteractableCollider::HasOverlappingActors()
{	
	return CurrentInteractableActorsInRange.Num() <= 0 ? false : true;
}

void UZAQInteractableCollider::UpdateOverlappingActorsTSet()
{
	GetOverlappingActors(CurrentInteractableActorsInRange);

	for (AActor* OverlappingActor : CurrentInteractableActorsInRange)
	{
		if (IsOverlappingActor(OverlappingActor)) return;
		
		CurrentInteractableActorsInRange.Remove(OverlappingActor);		
	}
}
