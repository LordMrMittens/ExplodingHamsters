// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class EXPLODINGHAMSTERS_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetupDoor(FVector _OpeningSpeed, float _OpeningDistance,  float _MovementSpeed);
	void OpenDoor();
	

private:
	float MovementSpeed;
	FVector OpeningDirection;
	FVector StartingPosition;
	float OpeningDistance;
	FVector TargetPosition;
	bool bShouldMove = false;
	bool bShouldReturn = false;
	void MoveDoor(FVector _TargetPosition);
	float DistanceOffset = 0.5f;

};
