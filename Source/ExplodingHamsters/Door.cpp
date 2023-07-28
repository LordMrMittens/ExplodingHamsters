// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bShouldMove)
	{
		if (bShouldReturn == false)
		{
			MoveDoor(TargetPosition);
		}
		else
		{
			MoveDoor(StartingPosition);
		}
	}
}

void ADoor::SetupDoor(FVector _OpeningSpeed, float _OpeningDistance, float _MovementSpeed)
{
	OpeningDirection = _OpeningSpeed;
	OpeningDistance = _OpeningDistance;
	MovementSpeed = _MovementSpeed;
	StartingPosition = GetActorLocation();
	TargetPosition = StartingPosition + OpeningDirection.GetSafeNormal() * OpeningDistance;
}

void ADoor::OpenDoor()
{
	bShouldMove = true;
}

void ADoor::MoveDoor(FVector _TargetPosition)
{
	FVector NewPosition = FMath::VInterpTo(GetActorLocation(), _TargetPosition, GetWorld()->GetDeltaSeconds(), MovementSpeed);
	SetActorLocation(NewPosition);
	float DistanceToTarget = FVector::Dist(GetActorLocation(), _TargetPosition);
	if (DistanceToTarget<DistanceOffset)
	{
		if (_TargetPosition != StartingPosition)
		{
			bShouldReturn = true;
			UE_LOG(LogTemp, Warning, TEXT("Should be returning"));
		}
		else
		{
			bShouldMove = false;
			bShouldReturn = false;
			UE_LOG(LogTemp, Warning, TEXT("Has Returned"));
		}
	}
}
