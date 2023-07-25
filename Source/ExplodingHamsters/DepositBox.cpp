// Fill out your copyright notice in the Description page of Project Settings.


#include "DepositBox.h"
#include "DepositBoxTrigger.h"
#include "ExplodingHamstersGM.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADepositBox::ADepositBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADepositBox::BeginPlay()
{
	Super::BeginPlay();
	StartingLocation = GetActorLocation();
	DepositBoxTrigger = FindComponentByClass<UDepositBoxTrigger>();
	ExplodingHamstersGameMode = Cast<AExplodingHamstersGM>(UGameplayStatics::GetGameMode(GetWorld()));

	if (DepositBoxTrigger)
	{
		DepositBoxTrigger->OnDepositBoxIsFull.AddDynamic(this, &ADepositBox::OnDepositBoxIsFull);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Deposit Box Not Found"));
	}
}

// Called every frame
void ADepositBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveBox(DeltaTime);
}

void ADepositBox::OnDepositBoxIsFull(ADepositBox *DepositBox)
{
	if (!bBoxIsEmptying)
	{
		bBoxIsEmptying = true;
		bBoxIsMoving = true;
		bBoxIsReturning = false;
	}
}

void ADepositBox::UpdateScore()
{
	if(ExplodingHamstersGameMode != nullptr && DepositBoxTrigger != nullptr){
		ExplodingHamstersGameMode->UpdateScore(DepositBoxTrigger->ContainedHamsters.Num());
	}
}
void ADepositBox::MoveBox(float DeltaTime){
	if (bBoxIsMoving)
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation += MovementVelocity * DeltaTime;
		SetActorLocation(CurrentLocation);
		float DistanceTraveled = FVector::Distance(StartingLocation, GetActorLocation());
		if (DistanceTraveled >= MovementDistance)
		{
			SetActorLocation(StartingLocation + MovementVelocity.GetSafeNormal() * MovementDistance);
			MovementVelocity *= -1;
			bBoxIsReturning = true;
			DepositBoxTrigger->ResetDepositBox();
			bBoxIsEmptying = false;
		}
		else if (bBoxIsReturning && DistanceTraveled <= 3.0f)
		{
			SetActorLocation(StartingLocation);
			bBoxIsMoving = false;
			bBoxIsReturning = false;
			MovementVelocity *= -1;
		}
	}
}
