// Fill out your copyright notice in the Description page of Project Settings.


#include "DepositBoxTrigger.h"
#include "HamsterEnums.h"

UDepositBoxTrigger::UDepositBoxTrigger(){
PrimaryComponentTick.bCanEverTick = true;

}

void UDepositBoxTrigger::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UDepositBoxTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TArray<AActor *> DetectedActors;
	GetOverlappingActors(DetectedActors);
	for (AActor* Actor: DetectedActors)
	{
		if(Actor->ActorHasTag("Hamster") && Actor->ActorHasTag("Grabbed")== false){
			if(ContainedHamsters.Contains(Actor) == false){
				ContainedHamsters.Add(Actor);
			}
		}
	}
	int HamsterCount = ContainedHamsters.Num();
	UE_LOG(LogTemp, Display, TEXT("Hamster Count : %i"), HamsterCount);
	ContainedHamsters.Empty();
	DetectedActors.Empty();

	// ...
}