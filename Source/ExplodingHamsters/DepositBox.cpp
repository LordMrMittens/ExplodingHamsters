// Fill out your copyright notice in the Description page of Project Settings.

#include "DepositBox.h"
#include "HamsterEnums.h"
#include "DepositBoxTrigger.h"
#include "ExplodingHamstersGM.h"
#include "Kismet/GameplayStatics.h"
#include "Door.h"
#include "Explosive.h"

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
	GetComponents<USceneComponent>(HamsterLocations);
	for (int32 i = 0; i < HamsterLocations.Num(); i++)
	{
		if (HamsterLocations[i] == GetRootComponent())
		{
			HamsterLocations.RemoveAt(i);
		} else {
			LocationsTMap.Add(HamsterLocations[i], nullptr);
		}
	}
}

// Called every frame
void ADepositBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bBoxIsMoving)
	{
		if (bBoxIsReturning == false)
		{
			MoveBox(MovementVelocity, StartingLocation);
		}
		else
		{
			MoveBox(-MovementVelocity, StartingLocation + MovementVelocity.GetSafeNormal() * MovementDistance);
		}
	}
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
void ADepositBox::MoveBox(FVector _MovementVelocity, FVector _StartingPoint)
{
		for (auto &Location : LocationsTMap)
		{
			if (Location.Value != nullptr)
			{
			Location.Value->bShouldForcefullyMove = false;
			}
		}
		float DeltaTime = GetWorld()->GetDeltaSeconds();
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation += _MovementVelocity * DeltaTime;
		SetActorLocation(CurrentLocation);
		float DistanceTraveled = FVector::Distance(_StartingPoint, GetActorLocation());
		if (DistanceTraveled >= MovementDistance)
		{
			if (bBoxIsReturning)
			{
			SetActorLocation(StartingLocation);
			bBoxIsMoving = false;
			bBoxIsReturning = false;
			ExplodingHamstersGameMode->ABoxCompleted();
			}
			else
			{
			SetActorLocation(_StartingPoint + _MovementVelocity.GetSafeNormal() * MovementDistance);
			UpdateScore();
			DepositBoxTrigger->ResetDepositBox();
			FTimerHandle ReturnMovementDelayTimerHandle;
			bBoxIsMoving = false;
			GetWorldTimerManager().SetTimer(ReturnMovementDelayTimerHandle, this, &ADepositBox::StartReturnMovement, ReturnMovementDelay, false);
			}
		}
}

void ADepositBox::GameOverCount()
{
		if (Door != nullptr)
		{
			Door->OpenDoor();
		}
		bBoxIsEmptying = true;
		bBoxIsMoving = true;
		bBoxIsReturning = false;
}

void ADepositBox::StartReturnMovement()
{
	bBoxIsMoving = true;
	bBoxIsReturning = true;
	bBoxIsEmptying = false;
}

void ADepositBox::SetHamsterSlot(AExplosive* Hamster)
{
	for (auto& Location : LocationsTMap)
	{
		if(Location.Value==nullptr){
			Location.Value = Hamster;
			Hamster->TargetLocation = Location.Key->GetComponentLocation();
			Hamster->bShouldForcefullyMove = true;
			break;
		}
	}
	
}

void ADepositBox::ClearHamsterSlots()
{
		for (auto& Location : LocationsTMap)
	{

		Location.Value = nullptr;
	}
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
