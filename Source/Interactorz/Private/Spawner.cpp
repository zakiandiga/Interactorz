// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Kismet/GameplayStatics.h"

#include "DebugHelpers/DebugMacros.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	if (bSpawnOnStart) return;

	GetWorldTimerManager().SetTimer(RespawnTimer, this, &ASpawner::SpawnActor, GetRespawnTime(), false);
	
}


void ASpawner::SpawnActor()
{
	Debug_Log(Warning, TEXT("ActorSpawned!"));
	
	if (ActorToSpawnClass == nullptr) return;

	float RandomYaw = FMath::FRandRange(0.f, 360.f);
	FRotator SpawnRotation = GetActorRotation();
	SpawnRotation.Yaw = RandomYaw;
	AActor* ActorToSpawn = GetWorld()->SpawnActor<AActor>(ActorToSpawnClass, GetActorLocation(), SpawnRotation);
	SpawnedActor = Cast<AActor>(ActorToSpawn);

	if (!bIsRespawnable) return;

	SpawnedActor->OnDestroyed.AddDynamic(this, &ASpawner::RestartRespawnTimer);
}

void ASpawner::RestartRespawnTimer(AActor* DestroyedActor)
{
	GetWorldTimerManager().SetTimer(RespawnTimer, this, &ASpawner::SpawnActor, GetRespawnTime(), false);
}

