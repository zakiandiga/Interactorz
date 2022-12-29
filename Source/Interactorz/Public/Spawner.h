// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class INTERACTORZ_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawner();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Spawner")
	TSubclassOf<AActor> ActorToSpawnClass;

	AActor* SpawnedActor = nullptr;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Spawner | Timer")
	bool bSpawnOnStart = false;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Spawner | Timer")
	bool bIsRespawnable = true;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Spawner | Timer")
	float MinRespawnTime = 1.f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Spawner | Timer")
	float MaxRespawnTime = 3.f;

	UPROPERTY()
	FTimerHandle RespawnTimer;

	//bIsRandomizingLocation
	//SpawnRangeX & SpawnRangeY
	//GetRandomSpawnTransform()

	void SpawnActor();

	UFUNCTION()
	void RestartRespawnTimer(AActor* DestroyedActor);

	UFUNCTION()
	float GetRespawnTime() { return MinRespawnTime == MaxRespawnTime ? MinRespawnTime : FMath::FRandRange(MinRespawnTime, MaxRespawnTime); }

public:

	UFUNCTION(BlueprintPure, Category = "Spawner | Timer")
	FORCEINLINE FTimerHandle GetRespawnTimer() { return RespawnTimer; }

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	FORCEINLINE void SetIsRespawnable(bool SetRespawnable) { bIsRespawnable = bIsRespawnable; }

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	FORCEINLINE bool GetIsRespawnable() { return bIsRespawnable; }
};
