// Fill out your copyright notice in the Description page of Project Settings.


#include "Explosive.h"
#include "Kismet/GameplayStatics.h"
#include "Hamster.h"
#include "ExplodingHamstersGM.h"
#include "GameplayOptionsDataAsset.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "CountdownWidget.h"
#include "EHPlayerController.h"


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
	

	    GameMode = Cast<AExplodingHamstersGM>(GetWorld()->GetAuthGameMode());
        if (GameMode)
    {
        GameMode->BoxStartedMoving.AddDynamic(this, &AExplosive::OnBoxIsMoving);
        GameMode->BoxCompletedMovement.AddDynamic(this, &AExplosive::OnBoxStopped);
		if(GameMode->GameplayData){
			ExplosionTime = GameMode->GameplayData->GameplayOptions.HamsterExplosionTimer; //needs to be tidied and refactored
			UE_LOG(LogTemp, Error, TEXT("Gameplay Data timer : %f Exploding timer = %f"), GameMode->GameplayData->GameplayOptions.HamsterExplosionTimer, ExplosionTime);
		}
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Gamemode is null pointer"));
    }
	GetWorldTimerManager().SetTimer(ExplosionTimerHandle, this, &AExplosive::StartExploding, ExplosionTime, false);
	OriginalScale = GetActorScale3D().X;
	TimeElapsed = 0.f;
	
}

// Called every frame
void AExplosive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bIsInBox){
		GetWorldTimerManager().PauseTimer(ExplosionTimerHandle);
		SetActorScale3D(FVector(OriginalScale,OriginalScale,OriginalScale));
	}
	if(IsCloseToExploding() && GetWorldTimerManager().IsTimerPaused(ExplosionTimerHandle)==false){
		
		ShowExplosionFeedback();
	}

}
void AExplosive::StartExploding(){
	TArray<AActor*> AllHamsters;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Hamster"), AllHamsters);
	SpawnExplosion();
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
		GetWorldTimerManager().UnPauseTimer(ExplosionTimerHandle);
	}
}

void AExplosive::Explode()
{
	float ExplosionTimer = FMath::RandRange(0.0f, 1.5f);
	FTimerHandle RandomisedExplosionHandle;
	GetWorldTimerManager().SetTimer(RandomisedExplosionHandle, this, &AExplosive::SpawnExplosion, ExplosionTimer, false);
}

void AExplosive::SpawnExplosion()
{
		if (ExplosionEffects)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionEffects, GetActorLocation(), GetActorRotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),ExplosionSound, GetActorLocation());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Actor %s Went Boom without an effect"), *GetActorNameOrLabel());
	}
	this->Destroy();
}

// Called to bind functionality to input
void AExplosive::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool AExplosive::IsCloseToExploding()
{
	return GetWorldTimerManager().GetTimerRemaining(ExplosionTimerHandle) < DisplaySecondsBeforeExplosion;
}

void AExplosive::ShowExplosionFeedback()
{
	AEHPlayerController * PlayerController = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	if(PlayerController!= nullptr){
	UCountdownWidget * CountdownWidget = Cast<UCountdownWidget>(CreateWidget(PlayerController, CountdownWidgetClass, TEXT("CD")));
	if(CountdownWidget!=nullptr){
		CountdownWidget->TimeRemainingText = (int32)GetWorldTimerManager().GetTimerRemaining(ExplosionTimerHandle);
		//CountdownWidget->ExplodingHamster = this;
		CountdownWidget->AddToViewport(0);
	}}
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	TimeElapsed += DeltaTime;
	float ScalingFactor = FMath::Sin(2 * PI * TimeElapsed * FeedbackFrequency);
    CurrentScale = OriginalScale + (MaxScale - OriginalScale) * 0.5f * (1.0f + ScalingFactor);
    SetActorScale3D(FVector(CurrentScale));
}

