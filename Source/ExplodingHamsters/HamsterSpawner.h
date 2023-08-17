// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HamsterSpawner.generated.h"

class AHamsterSpawnPoint;

UCLASS()
class EXPLODINGHAMSTERS_API AHamsterSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHamsterSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Spawning | Spawning Locations")
	TArray<AHamsterSpawnPoint *> HamsterSpawnLocations;
	TArray<AHamsterSpawnPoint *> GetHamsterSpawnLocations();
	AHamsterSpawnPoint* GetAvailableSpawnPoint(TArray<AHamsterSpawnPoint *> TakenSpawnPoints);

private:
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bSpawnTwoAtStart;
	UPROPERTY(VisibleAnywhere, Category = "Spawning | Spawning Timers")
	float HamsterSpawnTime;
	UPROPERTY(EditAnywhere, Category = "Spawning | Spawning Timers")
	float MinSpawnTime;
	UPROPERTY(EditAnywhere, Category = "Spawning | Spawning Timers")
	float MaxSpawnTime;
	UPROPERTY(EditAnywhere, Category = "Spawning | Spawning Timers")
	float AmountToSpeedUp = 0.08f;

	UPROPERTY(EditAnywhere, Category = "Spawning | Spawning Timers")
	int32 SpawnsBeforeSpeedUp = 5;
	int32 CurrentSpawns = 0;

	UPROPERTY(EditAnywhere, Category = "Spawning | Spawning Timers")
	float ExtraSpawnSpawnsBeforeSpeedUpCounter = 1.0f; // this is the amount of time in seconds the game needs to speed up before adding another spawn before the enxt speed up
	float SpawningSpedUp = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Spawning | Spawning Timers")
	float AddSpawningHamsterTimer = 75;
	UPROPERTY(EditAnywhere, Category = "Spawning | Spawning Timers")
	int32 MaxNumberOfHamstersToSpawn = 4;
	UPROPERTY(EditAnywhere, Category = "Spawning | Spawning Timers")
	int32 NumberOfHamstersToSpawn = 1;

	FTimerHandle AddSpawningHamsterHandle;
	void AddHamsterToSpawn();

	FTimerHandle SpawnTimerHandle;

	void SpawnHamster();

	UFUNCTION()
	void OnBoxIsMoving();
	UFUNCTION()
	void OnBoxStopped();
	UFUNCTION()
	void OnGameIsOver();

	class AExplodingHamstersGM *GameMode;
};
