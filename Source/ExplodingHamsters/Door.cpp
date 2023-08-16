// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

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

void ADoor::SetupDoor(FVector _OpeningSpeed, float _OpeningDistance, float _MovementSpeed, float _CloseDelay)
{
	OpeningDirection = _OpeningSpeed;
	OpeningDistance = _OpeningDistance;
	MovementSpeed = _MovementSpeed;
	CloseDelay = _CloseDelay;
	StartingPosition = GetActorLocation();
	TargetPosition = StartingPosition + OpeningDirection.GetSafeNormal() * OpeningDistance;
}

void ADoor::OpenDoor()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DoorOpensSound, GetActorLocation());
	bShouldMove = true;
}

void ADoor::CloseDoor()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DoorClosesSound, GetActorLocation());
	bShouldReturn = true;
	bShouldMove = true;
}

void ADoor::MoveDoor(FVector _TargetPosition)
{
	if(DoorServoSoundComponent ==nullptr){
		DoorServoSoundComponent = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), DoorServoSound, GetActorLocation());
	}
	DoorServoSoundComponent->Play();
	FVector NewPosition = FMath::VInterpTo(GetActorLocation(), _TargetPosition, GetWorld()->GetDeltaSeconds(), MovementSpeed);
	SetActorLocation(NewPosition);
	float DistanceToTarget = FVector::Dist(GetActorLocation(), _TargetPosition);
	if (DistanceToTarget<DistanceOffset)
	{
		if (_TargetPosition != StartingPosition)
		{
			FTimerHandle DoorCloseDelayTimerHandle;
			GetWorldTimerManager().SetTimer(DoorCloseDelayTimerHandle, this, &ADoor::CloseDoor, CloseDelay, false);
			bShouldMove = false;
			
			DoorServoSoundComponent->Stop();
		}
		else
		{
			bShouldMove = false;
			bShouldReturn = false;
			
			DoorServoSoundComponent->Stop();
		}
	}
}
