// Fill out your copyright notice in the Description page of Project Settings.


#include "HamsterSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "ExplodingHamstersGM.h"
#include "HamsterSpawnPoint.h"
#include "GameplayOptionsDataAsset.h"

// Sets default values
AHamsterSpawner::AHamsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AHamsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	    GameMode = Cast<AExplodingHamstersGM>(GetWorld()->GetAuthGameMode());
    if (GameMode)
    {
        GameMode->BoxStartedMoving.AddDynamic(this, &AHamsterSpawner::OnBoxIsMoving);
        GameMode->BoxCompletedMovement.AddDynamic(this, &AHamsterSpawner::OnBoxStopped);
		GameMode->OnGameOver.AddDynamic(this, &AHamsterSpawner::OnGameIsOver);
		if(GameMode->GameplayData){
			MaxSpawnTime = GameMode->GameplayData->GameplayOptions.MaxHamsterSpawnDelay;
			MinSpawnTime = GameMode->GameplayData->GameplayOptions.MinHamsterSpawnDelay;
		}
    } else{
		UE_LOG(LogTemp, Error, TEXT("Gamemode is null pointer"));
	}
	HamsterSpawnTime = MaxSpawnTime;
	GetWorldTimerManager().SetTimer(SpawnTimerHandle,this,&AHamsterSpawner::SpawnHamster,HamsterSpawnTime,false);
	GetWorldTimerManager().SetTimer(AddSpawningHamsterHandle, this, &AHamsterSpawner::AddHamsterToSpawn,AddSpawningHamsterTimer, true);
	if(bSpawnTwoAtStart){
		SpawnHamster();
		SpawnHamster();
	}
	
}

// Called every frame
void AHamsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHamsterSpawner::AddHamsterToSpawn()
{
	if (NumberOfHamstersToSpawn < MaxNumberOfHamstersToSpawn)
	{
		NumberOfHamstersToSpawn++;
		HamsterSpawnTime += (AmountToSpeedUp*5);
	}
}

void AHamsterSpawner::SpawnHamster()
{
	for (int32 i = 0; i < NumberOfHamstersToSpawn; i++)
	{
		int SpawnLocationIndex = FMath::RandRange(0, HamsterSpawnLocations.Num() - 1);
		HamsterSpawnLocations[SpawnLocationIndex]->SpawnHamster();
	}

	CurrentSpawns++;
	if (CurrentSpawns >= SpawnsBeforeSpeedUp)
	{
		HamsterSpawnTime = FMath::Max(MinSpawnTime, HamsterSpawnTime - AmountToSpeedUp);
		SpawningSpedUp += AmountToSpeedUp;
		if(SpawningSpedUp >= ExtraSpawnSpawnsBeforeSpeedUpCounter){
			SpawnsBeforeSpeedUp ++;
		}
		CurrentSpawns=0;
	}
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AHamsterSpawner::SpawnHamster, HamsterSpawnTime, false);
}

void AHamsterSpawner::OnBoxIsMoving()
{
	GetWorldTimerManager().PauseTimer(SpawnTimerHandle);
}

void AHamsterSpawner::OnBoxStopped()
{
	GetWorldTimerManager().UnPauseTimer(SpawnTimerHandle);
	
}

void AHamsterSpawner::OnGameIsOver()
{
	GetWorldTimerManager().PauseTimer(SpawnTimerHandle);
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
}
