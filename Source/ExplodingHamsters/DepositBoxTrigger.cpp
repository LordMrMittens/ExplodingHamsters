// Fill out your copyright notice in the Description page of Project Settings.

#include "DepositBoxTrigger.h"
#include "HamsterEnums.h"
#include "Hamster.h"
#include "Explosive.h"
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
		AExplosive *Hamster;
		if (IsValidHamster(Actor, Hamster, bShouldItExplode))
		{
			
			ContainedHamsters.Add(Actor);
			if(bShouldItExplode){
				Hamster->StartExploding();
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
void UDepositBoxTrigger::DestroyDepositBox()
{
	for (AActor *Actor : ContainedHamsters)
	{
		if (Actor != nullptr)
		{
			AExplosive *Explosive = Cast<AExplosive>(Actor);
			if (Explosive != nullptr)
			{
				Explosive->Explode();
			}
		}
	}
	ContainedHamsters.Empty();
}

bool UDepositBoxTrigger::IsValidHamster(AActor *HamsterActor, AExplosive *&DepositedHamster, bool &ShouldExplode)
{
	if (HamsterActor != nullptr && HamsterActor->ActorHasTag("Hamster") && HamsterActor->ActorHasTag("Grabbed") == false)
	{
		DepositedHamster = Cast<AExplosive>(HamsterActor);
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