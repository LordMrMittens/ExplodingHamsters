// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindNewLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include  "Kismet/GameplayStatics.h"
#include "AIController.h"

UBTTask_FindNewLocation::UBTTask_FindNewLocation()
{
    NodeName = TEXT("Find New Target Location");
}

EBTNodeResult::Type UBTTask_FindNewLocation::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    TArray<AActor *> levelActors;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Level"), levelActors);
    if (levelActors.Num() == 1)
    {
        Level = levelActors[0];
        LevelMesh = Level->GetComponentByClass<UStaticMeshComponent>();
        if (LevelMesh != nullptr)
        {
            LevelMesh->UpdateBounds();
            LevelMesh->GetLocalBounds(MinBounds, MaxBounds);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("No Level static mesh found"));
    }

    
    FVector NewTarget = GetRandomLocationNearby(OwnerComp);
    OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), NewTarget);
    return EBTNodeResult::Succeeded;
}

FVector UBTTask_FindNewLocation::GetRandomLocationNearby(UBehaviorTreeComponent &OwnerComp)
{
    FVector Target = FVector::ZeroVector;
    float XLocation = FMath::RandRange(MinBounds.X, MaxBounds.X);
    float YLocation = FMath::RandRange(MinBounds.Y, MaxBounds.Y);
    AAIController* AiController = OwnerComp.GetAIOwner();
    AActor* OwnerActor = AiController->GetPawn();
    if (OwnerActor != nullptr)
    {
        Target = FVector(XLocation, YLocation, OwnerActor->GetActorLocation().Z);
    } else {
        UE_LOG(LogTemp, Display, TEXT("Pawn is null"));
    }
    return Target;
};
