// Fill out your copyright notice in the Description page of Project Settings.


#include "HamsterSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Hamster.h"
#include "HamAIController.h"

#define ENUM_LENGTH(EnumType) (static_cast<int32>(EnumType::EnumCount))

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
	HamsterSpawnTime = MaxSpawnTime;
	GetWorldTimerManager().SetTimer(SpawnTimerHandle,this,&AHamsterSpawner::SpawnHamster,HamsterSpawnTime,false);

	
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

void AHamsterSpawner::SpawnHamster()
{
	int SpawnLocationIndex = FMath::RandRange(0, HamsterSpawnLocations.Num()-1);

	FTransform SpawnTransForm = HamsterSpawnLocations[SpawnLocationIndex]->GetActorTransform();
	AHamster *Hamster = Cast<AHamster>(UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), HamsterClass, SpawnTransForm));
	if (Hamster != nullptr)
	{
		EHamsterEnums HamsterColour;
		int32 ColourLength = ENUM_LENGTH(EHamsterEnums);
		int32 RandomColourIndex = FMath::RandRange(0, ColourLength - 1);
		HamsterColour = static_cast<EHamsterEnums>(RandomColourIndex);
		Hamster->SetHamsterColour(HamsterColour);

		AHamAIController* AIController = Cast<AHamAIController>(GetWorld()->SpawnActor(HamsterAIClass));
		if(AIController !=nullptr){
			AIController->Possess(Hamster);
		} else{
			UE_LOG(LogTemp, Error, TEXT("No AI Controller"));
		}

		UGameplayStatics::FinishSpawningActor(Hamster, SpawnTransForm);
	}

	HamsterSpawnTime = FMath::Max(MinSpawnTime, HamsterSpawnTime - .2f);
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AHamsterSpawner::SpawnHamster, HamsterSpawnTime, false);
}
