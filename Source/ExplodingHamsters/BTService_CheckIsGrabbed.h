// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CheckIsGrabbed.generated.h"

/**
 * 
 */
UCLASS()
class EXPLODINGHAMSTERS_API UBTService_CheckIsGrabbed : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	public:
	UBTService_CheckIsGrabbed();

	protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
private:
	
	class AHamster* Hamster;
	class APawn* HamPawn;
	
};
