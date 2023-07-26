// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HamsterSpawner.generated.h"

class AHamster;
class AHamAIController;

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

	UPROPERTY(EditAnywhere, Category="Spawning | Spawning Locations")
	TArray<AActor*> HamsterSpawnLocations;
private:

	UPROPERTY(EditAnywhere, Category="Debug")
	bool bSpawnTwoAtStart;
	UPROPERTY(VisibleAnywhere, Category="Spawning | Spawning Timers")
	float HamsterSpawnTime;
	UPROPERTY(EditAnywhere, Category="Spawning | Spawning Timers")
	float MinSpawnTime;
	UPROPERTY(EditAnywhere, Category="Spawning | Spawning Timers")
	float MaxSpawnTime;


	FTimerHandle SpawnTimerHandle;

	void SpawnHamster();

	UPROPERTY(EditAnywhere, Category="Spawning | Prefab")
	TSubclassOf<AHamster> HamsterClass;
	UPROPERTY(EditAnywhere, Category="Spawning | Prefab")
	TSubclassOf<AHamAIController> HamsterAIClass;
	UFUNCTION()
	void OnBoxIsMoving();
	UFUNCTION()
	void OnBoxStopped();

	class AExplodingHamstersGM* GameMode;
    
};
