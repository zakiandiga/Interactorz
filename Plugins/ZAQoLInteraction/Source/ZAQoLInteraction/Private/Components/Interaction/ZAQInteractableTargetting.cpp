// Copyright Zaki Agraraharja. All Rights Reserved.

#include "Components/Interaction/ZAQInteractableTargetting.h"
#include "Components/Interaction/ZAQInteractableCollider.h"
#include "Components/Interaction/ZAQInteractionHandler.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"

UZAQInteractableTargetting::UZAQInteractableTargetting()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UZAQInteractableTargetting::BeginPlay()
{
	Super::BeginPlay();

	PlayerCamera = Cast<UCameraComponent>(GetOwner()->GetComponentByClass(UCameraComponent::StaticClass()));
	CameraBoom = Cast<USpringArmComponent>(GetOwner()->GetComponentByClass(USpringArmComponent::StaticClass()));
	InteractableCollider = Cast<UZAQInteractableCollider>(GetOwner()->GetComponentByClass(UZAQInteractableCollider::StaticClass()));
	InteractionHandler = Cast<UZAQInteractionHandler>(GetOwner()->GetComponentByClass(UZAQInteractionHandler::StaticClass()));
}

void UZAQInteractableTargetting::TracingInteractable()
{
	if (PlayerCamera == nullptr && CameraBoom == nullptr) return;

	FVector StartPoint = PlayerCamera->GetComponentLocation() + (PlayerCamera->GetForwardVector() * CameraBoom->TargetArmLength);
	FVector EndPoint = StartPoint + (PlayerCamera->GetForwardVector() * 400.f);

	FHitResult CurrentHitResult;
	FCollisionQueryParams LineTraceParams;
	LineTraceParams.AddIgnoredActor(GetOwner());
	
	GetWorld()->LineTraceSingleByChannel(CurrentHitResult, StartPoint, EndPoint, ECollisionChannel::ECC_Visibility, LineTraceParams);

	AActor* HitActor = CurrentHitResult.GetActor();

	TryAssignInteractable(HitActor);	
}


void UZAQInteractableTargetting::TryAssignInteractable(AActor* TracedActor)
{
	if (TracedActor == nullptr || !InteractionHandler->IsInteractable(TracedActor))
	{
		if (InteractionHandler->GetCurrentInteractableActor() == nullptr) return;

		InteractionHandler->ClearInteractable();
		OnInteractableGone.Broadcast();
		return;
	}

	if (TracedActor == InteractionHandler->GetCurrentInteractableActor()) return;

	InteractionHandler->AssignInteractable(TracedActor);
	OnInteractableFound.Broadcast(TracedActor);
}

bool UZAQInteractableTargetting::IsTracing() const
{
	return InteractableCollider && InteractableCollider->HasOverlappingActors();
}


void UZAQInteractableTargetting::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsTracing()) return;
	
	TracingInteractable();
}

