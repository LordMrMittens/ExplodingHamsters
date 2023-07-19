// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindNewLocation.generated.h"

/**
 *
 */
UCLASS()
class EXPLODINGHAMSTERS_API UBTTask_FindNewLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FindNewLocation();

		UPROPERTY()
	AActor *Level;
	UPROPERTY()
	UStaticMeshComponent *LevelMesh;

	FVector MinBounds;
	FVector MaxBounds;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;

	private:
	private:
	FVector GetRandomLocationNearby(UBehaviorTreeComponent &OwnerComp);
};
