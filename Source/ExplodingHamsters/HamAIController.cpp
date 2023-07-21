// Fill out your copyright notice in the Description page of Project Settings.


#include "HamAIController.h"
#include "AI/Navigation/NavigationBounds.h"
#include "Kismet/GameplayStatics.h"

AHamAIController::AHamAIController()
{

    PrimaryActorTick.bCanEverTick = true;
}

void AHamAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AHamAIController::BeginPlay()
{
    Super::BeginPlay();
    if (BehaviorTree != nullptr)
    {

        RunBehaviorTree(BehaviorTree);
    }
}
