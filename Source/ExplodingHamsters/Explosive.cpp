// Fill out your copyright notice in the Description page of Project Settings.


#include "Explosive.h"
#include "Kismet/GameplayStatics.h"
#include "Hamster.h"
#include "ExplodingHamstersGM.h"


// Sets default values
AExplosive::AExplosive()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExplosive::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(ExplosionTimerHandle, this, &AExplosive::StartExploding, ExplosionTime, false);

	    GameMode = Cast<AExplodingHamstersGM>(GetWorld()->GetAuthGameMode());
        if (GameMode)
    {
        GameMode->BoxStartedMoving.AddDynamic(this, &AExplosive::OnBoxIsMoving);
        GameMode->BoxCompletedMovement.AddDynamic(this, &AExplosive::OnBoxStopped);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Gamemode is null pointer"));
    }
	
}

// Called every frame
void AExplosive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bIsInBox){
		GetWorldTimerManager().PauseTimer(ExplosionTimerHandle);
	}

}
void AExplosive::StartExploding(){
	TArray<AActor*> AllHamsters;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Hamster"), AllHamsters);
	Explode();
	for (AActor* HamsterActor : AllHamsters){
		AExplosive* Explosive = Cast<AExplosive>(HamsterActor);
		AHamster* Hamster = Cast<AHamster>(HamsterActor);
		if(Hamster != nullptr && Explosive !=nullptr){
			if (Hamster->bIsInBox == false)
			{
				Explosive->Explode();
			}
			
		}

	}
	if (GameMode) {
		GameMode->OnGameIsOver();
	} else {
		UE_LOG(LogTemp, Error, TEXT("Could not end game because game mode is null"));
	}
}

void AExplosive::OnBoxIsMoving()
{
	if (bIsInBox == false)
	{
		GetWorldTimerManager().PauseTimer(ExplosionTimerHandle);
	}
}

void AExplosive::OnBoxStopped()
{
	if (bIsInBox == false)
	{
		GetWorldTimerManager().PauseTimer(ExplosionTimerHandle);
	}
}

void AExplosive::Explode()
{

	UE_LOG(LogTemp, Error, TEXT("Actor %s Went Boom"), *GetActorNameOrLabel());
	this->Destroy();
}

// Called to bind functionality to input
void AExplosive::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

