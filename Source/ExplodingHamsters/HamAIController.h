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
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	//FVector GetRandomLocationNearby();

	UPROPERTY(EditAnywhere, Category = "Parameters")
	class UBehaviorTree *BehaviorTree;

	UPROPERTY(VisibleAnywhere, Category = "Parameters")
	APawn *AIPawn;
	UFUNCTION()
	void OnBoxIsMoving();
	UFUNCTION()
	void OnBoxStopped();
};
