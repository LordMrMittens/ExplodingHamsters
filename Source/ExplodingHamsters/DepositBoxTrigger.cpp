// Fill out your copyright notice in the Description page of Project Settings.

#include "DepositBoxTrigger.h"
#include "HamsterEnums.h"
#include "Hamster.h"
#include "DepositBox.h"

UDepositBoxTrigger::UDepositBoxTrigger()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDepositBoxTrigger::BeginPlay()
{
	Super::BeginPlay();
	// ...
}
void UDepositBoxTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TArray<AActor *> DetectedActors;
	GetOverlappingActors(DetectedActors);
	for (AActor *Actor : DetectedActors)
	{
		bool bShouldItExplode;
		AHamster *Hamster;
		if (IsValidHamster(Actor, Hamster, bShouldItExplode))
		{
			
			ContainedHamsters.Add(Actor);
			if(bShouldItExplode){
				//lose game dont clear it
				ResetDepositBox();
			}
		}
	}
	if (ContainedHamsters.Num() >= MaxHamsters)
	{
		OnDepositBoxIsFull.Broadcast(Cast<ADepositBox>(GetOwner()));
	}
}

void UDepositBoxTrigger::ResetDepositBox()
{
	for (AActor *Actor : ContainedHamsters)
	{
		if (Actor != nullptr)
			Actor->Destroy();
	}
	ContainedHamsters.Empty();
}

bool UDepositBoxTrigger::IsValidHamster(AActor *HamsterActor, AHamster *&DepositedHamster, bool &ShouldExplode)
{
	if (HamsterActor != nullptr && HamsterActor->ActorHasTag("Hamster") && HamsterActor->ActorHasTag("Grabbed") == false)
	{
		DepositedHamster = Cast<AHamster>(HamsterActor);
		if (DepositedHamster != nullptr && ContainedHamsters.Contains(HamsterActor) == false)
		{
			ShouldExplode = DepositedHamster->HamsterColour != BoxColour;
			DepositedHamster->SetInBox(true);
			return true;
		}
	}
	ShouldExplode = false;
	return false;
}