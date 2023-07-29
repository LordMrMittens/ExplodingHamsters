// Fill out your copyright notice in the Description page of Project Settings.

#include "DepositBox.h"
#include "HamsterEnums.h"
#include "DepositBoxTrigger.h"
#include "ExplodingHamstersGM.h"
#include "Kismet/GameplayStatics.h"
#include "Door.h"

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
	if(Door!= nullptr){
		Door->SetupDoor(DoorOpeningDirection,DoorOpeningDistance,DoorMovementSpeed,CloseDoorDelay);
	} else{
		UE_LOG(LogTemp, Error, TEXT("Door is null"));
	}
}

// Called every frame
void ADepositBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveBox();
}

void ADepositBox::OnDepositBoxIsFull(ADepositBox *DepositBox)
{
	if (!bBoxIsEmptying)
	{
		if(Door!=nullptr){
			Door->OpenDoor();
		}
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
void ADepositBox::MoveBox()
{
	
	if (bBoxIsMoving)
	{
		float DeltaTime = GetWorld()->GetDeltaSeconds();
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation += MovementVelocity * DeltaTime;
		SetActorLocation(CurrentLocation);
		float DistanceTraveled = FVector::Distance(StartingLocation, GetActorLocation());
		if (DistanceTraveled >= MovementDistance)
		{
			SetActorLocation(StartingLocation + MovementVelocity.GetSafeNormal() * MovementDistance);
			UpdateScore();
			DepositBoxTrigger->ResetDepositBox();
			FTimerHandle ReturnMovementDelayTimerHandle;
			bBoxIsMoving = false;
			GetWorldTimerManager().SetTimer(ReturnMovementDelayTimerHandle, this, &ADepositBox::StartReturnMovement, ReturnMovementDelay, false);
			
		}
		else if (bBoxIsReturning && DistanceTraveled <= 10.0f)
		{
			SetActorLocation(StartingLocation);
			bBoxIsMoving = false;
			bBoxIsReturning = false;
			MovementVelocity *= -1;
			ExplodingHamstersGameMode->ABoxCompleted();
		}
	}
}

void ADepositBox::GameOverCount()
{
	if(Door!=nullptr){
		Door->OpenDoor();
	}
	bBoxIsEmptying = true;
	bBoxIsMoving = true;
	bBoxIsReturning = false;
}

void ADepositBox::StartReturnMovement()
{
	bBoxIsMoving = true;
	MovementVelocity *= -1;
	bBoxIsReturning = true;
	bBoxIsEmptying = false;
}

void ADepositBox::OnGameIsOver()
{
	if (DepositBoxTrigger != nullptr)
	{
		if (DepositBoxTrigger->ContainedHamsters.Num() > 0)
		{
			GetWorldTimerManager().SetTimer(GameOverTimerHandle, this, &ADepositBox::GameOverCount, GameOverDelay, false);
		}
	}
}
