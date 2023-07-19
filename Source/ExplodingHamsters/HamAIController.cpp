// Fill out your copyright notice in the Description page of Project Settings.


#include "HamAIController.h"
#include "AI/Navigation/NavigationBounds.h"
#include "Kismet/GameplayStatics.h"

AHamAIController::AHamAIController(){

    PrimaryActorTick.bCanEverTick = true;
}

void AHamAIController::BeginPlay()
{
    Super::BeginPlay();
        if (BehaviorTree != nullptr)
    {
        RunBehaviorTree(BehaviorTree);
    }
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
/*
FVector AHamAIController::GetRandomLocationNearby()
{
    FVector Target = FVector::ZeroVector;
    float XLocation = FMath::RandRange(MinBounds.X, MaxBounds.X);
    float YLocation = FMath::RandRange(MinBounds.Y, MaxBounds.Y);
    AActor *OwnerActor = GetPawn();
    if (OwnerActor != nullptr)
    {
        Target = FVector(XLocation, YLocation, OwnerActor->GetActorLocation().Z);
    } else {
        UE_LOG(LogTemp, Display, TEXT("Pawn is null"));
    }
    return Target;
};
*/