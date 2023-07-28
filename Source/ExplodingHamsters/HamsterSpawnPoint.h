// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HamsterSpawnPoint.generated.h"

class ADoor;
class AHamster;
class AHamAIController;

UCLASS()
class EXPLODINGHAMSTERS_API AHamsterSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHamsterSpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnHamster();

private:
	USceneComponent* RootComp;
	UPROPERTY(EditAnywhere)
	USceneComponent* TargetDirection;
	UPROPERTY(EditAnywhere)
	FVector ShootingForce;

	UPROPERTY(EditAnywhere)
	ADoor* Door;

	UPROPERTY(EditAnywhere)
	FVector OpeningDirection;

	UPROPERTY(EditAnywhere)
	float OpeningDistance;

	UPROPERTY(EditAnywhere)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, Category="Spawning | Prefab")
	TSubclassOf<AHamster> HamsterClass;

	UPROPERTY(EditAnywhere, Category="Spawning | Prefab")
	TSubclassOf<AHamAIController> HamsterAIClass;



};
