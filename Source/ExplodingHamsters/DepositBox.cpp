// Fill out your copyright notice in the Description page of Project Settings.


#include "DepositBox.h"
#include "DepositBoxTrigger.h"

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
	DepositBoxTrigger = FindComponentByClass<UDepositBoxTrigger>();

	if (DepositBoxTrigger)
	{
		DepositBoxTrigger->OnDepositBoxIsFull.AddDynamic(this, &ADepositBox::OnDepositBoxIsFull);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Deposit Box Not Found"));
	}
}

// Called every frame
void ADepositBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADepositBox::OnDepositBoxIsFull(ADepositBox* DepositBox)
{
	UE_LOG(LogTemp, Warning, TEXT("Owner: %s, is full, passed parameter: %s"),* GetActorNameOrLabel(), *DepositBox->GetActorNameOrLabel());
}
