// Fill out your copyright notice in the Description page of Project Settings.


#include "HamAIController.h"
#include "AI/Navigation/NavigationBounds.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

AHamAIController::AHamAIController(){

    PrimaryActorTick.bCanEverTick = true;
        BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

    // Automatically generate the BlackboardData asset for each instance
    if (BlackboardData != nullptr)
    {
        BlackboardData = DuplicateObject<UBlackboardData>(BlackboardData, nullptr);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("DefaultBlackboardData is not set for the AI Controller!"));
    }
}

void AHamAIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);
        if (BlackboardData != nullptr) // Make sure you have assigned separate blackboard data to each AI controller instance in the editor
    {
        // Initialize the blackboard with the blackboard data specific to this AI controller instance
        UseBlackboard(BlackboardData, BlackboardComponent);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Blackboard data not set for the AI Controller!"));
    }

    if (BehaviorTree != nullptr)
    {
        RunBehaviorTree(BehaviorTree);
    }
}

void AHamAIController::BeginPlay()
{
    Super::BeginPlay();
    TArray<AActor *> levelActors;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Level"), levelActors);
    if (levelActors.Num() == 1)
    {
        Level = levelActors[0];
        LevelMesh = Level->GetComponentByClass<UStaticMeshComponent>();
        if(LevelMesh != nullptr){
            LevelMesh->UpdateBounds();
            LevelMesh->GetLocalBounds(MinBounds,MaxBounds);
        }
    } else {
        UE_LOG(LogTemp, Error, TEXT("No Level static mesh found"));
    }
}
