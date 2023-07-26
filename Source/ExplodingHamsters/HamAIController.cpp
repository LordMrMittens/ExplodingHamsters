// Fill out your copyright notice in the Description page of Project Settings.


#include "HamAIController.h"
#include "AI/Navigation/NavigationBounds.h"
#include "Kismet/GameplayStatics.h"
#include "ExplodingHamstersGM.h"
#include "GameFramework/CharacterMovementComponent.h"

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
    AExplodingHamstersGM* GameMode = Cast<AExplodingHamstersGM>(GetWorld()->GetAuthGameMode());
        if (GameMode)
    {
        GameMode->BoxStartedMoving.AddDynamic(this, &AHamAIController::OnBoxIsMoving);
        GameMode->BoxCompletedMovement.AddDynamic(this, &AHamAIController::OnBoxStopped);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Gamemode is null pointer"));
    }
}

void AHamAIController::OnBoxIsMoving()
{
    
    APawn* ControlledPawn = GetPawn();
    if (ControlledPawn)
    {
        UCharacterMovementComponent* MovementComponent = ControlledPawn->FindComponentByClass<UCharacterMovementComponent>();
        if (MovementComponent)
        {
            MovementComponent->MaxWalkSpeed = 0; // Set it to the default walk speed of the character
        }
    }
}

void AHamAIController::OnBoxStopped()
{
    APawn* ControlledPawn = GetPawn();
    if (ControlledPawn)
    {
        UCharacterMovementComponent* MovementComponent = ControlledPawn->FindComponentByClass<UCharacterMovementComponent>();
        if (MovementComponent)
        {
            MovementComponent->MaxWalkSpeed = 150; // Set it to the default walk speed of the character
        }
    }
}
