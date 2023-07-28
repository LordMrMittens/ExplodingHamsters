// Fill out your copyright notice in the Description page of Project Settings.


#include "HamsterSpawnPoint.h"
#include "Door.h"
#include "HamsterEnums.h"
#include "Kismet/GameplayStatics.h"
#include "Hamster.h"
#include "HamAIController.h"

#define ENUM_LENGTH(EnumType) (static_cast<int32>(EnumType::EnumCount))

// Sets default values
AHamsterSpawnPoint::AHamsterSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootC"));
	SetRootComponent(RootComp);
	TargetDirection = CreateDefaultSubobject<USceneComponent>(TEXT("Target Point"));
	TargetDirection->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AHamsterSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	if(Door != nullptr){
		Door->SetupDoor(OpeningDirection, OpeningDistance, MovementSpeed);
	}
	
}

// Called every frame
void AHamsterSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHamsterSpawnPoint::SpawnHamster()
{
	if (Door != nullptr)
	{
		Door->OpenDoor();
		AHamster *Hamster = Cast<AHamster>(UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), HamsterClass, GetActorTransform()));
		if (Hamster != nullptr)
		{
			EHamsterEnums HamsterColour;
			int32 ColourLength = ENUM_LENGTH(EHamsterEnums);
			int32 RandomColourIndex = FMath::RandRange(0, ColourLength - 1);
			HamsterColour = static_cast<EHamsterEnums>(RandomColourIndex);
			Hamster->SetHamsterColour(HamsterColour);
			Hamster->TargetLocation= TargetDirection->GetComponentLocation();
			AHamAIController *AIController = Cast<AHamAIController>(GetWorld()->SpawnActor(HamsterAIClass));
			if (AIController != nullptr)
			{
				AIController->Possess(Hamster);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("No AI Controller"));
			}
			UGameplayStatics::FinishSpawningActor(Hamster, GetActorTransform());

	}
}}
