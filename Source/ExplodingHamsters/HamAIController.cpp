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
            APawn *MyPawn = this->GetPawn();
        if (MyPawn != nullptr)
        {
            UE_LOG(LogTemp, Error, TEXT("AI %s, Has possessed< %s"), *this->GetActorNameOrLabel(), *MyPawn->GetActorNameOrLabel());
        } else {

            UE_LOG(LogTemp, Error, TEXT("AI %s, Has possessed a null pawn"), *this->GetActorNameOrLabel());
        }
    
}

void AHamAIController::BeginPlay()
{
    Super::BeginPlay();
    if (BehaviorTree != nullptr)
    {

        RunBehaviorTree(BehaviorTree);
    }
}
