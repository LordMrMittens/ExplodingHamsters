// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HamAIController.generated.h"

/**
 * 
 */
UCLASS()
class EXPLODINGHAMSTERS_API AHamAIController : public AAIController
{
	GENERATED_BODY()

public:
	AHamAIController();
	UPROPERTY()
	AActor *Level;
	UPROPERTY()
	UStaticMeshComponent *LevelMesh;

	FVector MinBounds;
	FVector MaxBounds;

protected:
	virtual void OnPossess(APawn *InPawn) override;
	
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Parameters")
	class UBehaviorTree *BehaviorTree;

	UPROPERTY(EditAnywhere, Category = "Parameters")
	class UBlackboardData *BlackboardData;

private:
	// FVector GetRandomLocationNearby();
	UBlackboardComponent *BlackboardComponent;

	UPROPERTY(VisibleAnywhere, Category = "Parameters")
	APawn *AIPawn;
};
