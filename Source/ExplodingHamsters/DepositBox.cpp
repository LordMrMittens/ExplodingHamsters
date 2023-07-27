// Fill out your copyright notice in the Description page of Project Settings.

#include "DepositBox.h"
#include "HamsterEnums.h"
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
	AExplodingHamstersGM* GameMode = Cast<AExplodingHamstersGM>(GetWorld()->GetAuthGameMode());
	if(GameMode!=nullptr){
		GameMode->OnGameOver.AddDynamic(this, &ADepositBox::OnGameIsOver);
	}
	StartingLocation = GetActorLocation();
	DepositBoxTrigger = FindComponentByClass<UDepositBoxTrigger>();
	if (DepositBoxTrigger != nullptr)
	{
		DepositBoxTrigger->SetupDepositBox(MaxHamsters, this);
	}
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
		ExplodingHamstersGameMode->ABoxIsMoving();
		bBoxIsEmptying = true;
		bBoxIsMoving = true;
		bBoxIsReturning = false;
	}
}

void ADepositBox::UpdateScore()
{
	if (ExplodingHamstersGameMode != nullptr && DepositBoxTrigger != nullptr)
	{
		ExplodingHamstersGameMode->UpdateScore(DepositBoxTrigger->ContainedHamsters.Num());
	}
}
void ADepositBox::MoveBox(float DeltaTime)
{
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
			UpdateScore();
			DepositBoxTrigger->ResetDepositBox();
			bBoxIsEmptying = false;
		}
		else if (bBoxIsReturning && DistanceTraveled <= 3.0f)
		{
			SetActorLocation(StartingLocation);
			bBoxIsMoving = false;
			bBoxIsReturning = false;
			MovementVelocity *= -1;
			ExplodingHamstersGameMode->ABoxCompleted();
		}
	}
}

void ADepositBox::OnGameIsOver()
{
	if (DepositBoxTrigger != nullptr)
	{
		if (DepositBoxTrigger->ContainedHamsters.Num() > 0)
		{
			ExplodingHamstersGameMode->ABoxIsMoving(); // this might not be needed or cause issues
			bBoxIsEmptying = true;
			bBoxIsMoving = true;
			bBoxIsReturning = false;
		}
	}
}
