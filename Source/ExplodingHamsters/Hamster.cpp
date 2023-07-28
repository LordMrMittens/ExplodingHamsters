// Fill out your copyright notice in the Description page of Project Settings.


#include "Hamster.h"
#include "HamsterEnums.h"

// Sets default values
AHamster::AHamster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHamster::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh = GetComponentByClass<UStaticMeshComponent>();
	if (StaticMesh != nullptr)
	{
		switch (HamsterColour)
		{
		case EHamsterEnums::Red:

			StaticMesh->SetMaterial(0, RedMaterial);
			break;

					case EHamsterEnums::Blue:

			StaticMesh->SetMaterial(0, BlueMaterial);
			break;
		
		default:
		UE_LOG(LogTemp, Error, TEXT("Hamster material not set"));
			break;
		}
	}
	
	
}

// Called every frame
void AHamster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bHasJustSpawned){
		InitialMovement();
	}

}

// Called to bind functionality to input
void AHamster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AHamster::SetPickedUp(bool _bIsPickedUp)
{
	bIsPickedUp = _bIsPickedUp;
	if (_bIsPickedUp == true)
	{
		Tags.Add("Grabbed");
	}
	else
	{
		Tags.Remove("Grabbed");
	}
}

void AHamster::SetInBox(bool _bbIsInBox)
{
		bIsInBox = _bbIsInBox;

}

void AHamster::SetHamsterColour(EHamsterEnums Colour)
{
	HamsterColour = Colour;
}

void AHamster::InitialMovement()
{
	
	FVector NewPosition = FMath::VInterpTo(GetActorLocation(), TargetLocation, GetWorld()->GetDeltaSeconds(), InitialMovementSpeed);
	SetActorLocation(NewPosition);
	float DistanceToTarget = FVector::Dist(GetActorLocation(), TargetLocation);
	if (DistanceToTarget<InitialMovementDistanceOffset)
	{
		bHasJustSpawned = false;
		UE_LOG(LogTemp, Display, TEXT("Stopped Moving"));
	}
}
