// Fill out your copyright notice in the Description page of Project Settings.


#include "DepositBoxTrigger.h"
#include "HamsterEnums.h"
#include "Hamster.h"
#include "DepositBox.h"

UDepositBoxTrigger::UDepositBoxTrigger(){
PrimaryComponentTick.bCanEverTick = true;

}

void UDepositBoxTrigger::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}
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
				AHamster* Hamster = Cast<AHamster>(Actor);
				if(Hamster!=nullptr){
					Hamster->SetInBox(true);
				}
			}
		}
	}
		if (ContainedHamsters.Num() >= MaxHamsters)
	{
		OnDepositBoxIsFull.Broadcast(Cast<ADepositBox>(GetOwner()));
	}
}

void UDepositBoxTrigger::ResetDepositBox(){
 for (AActor* Actor : ContainedHamsters){
	if(Actor!= nullptr)
	Actor->Destroy();
 }
ContainedHamsters.Empty();
 
}