// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HamsterEnums.h"
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "DepositBoxTrigger.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXPLODINGHAMSTERS_API UDepositBoxTrigger : public UBoxComponent
{
	GENERATED_BODY()

	public:	
	// Sets default values for this component's properties
	UDepositBoxTrigger();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	TArray<AActor*> ContainedHamsters;

UPROPERTY(EditAnywhere, BlueprintReadOnly)
    EHamsterEnums BoxColour;
};
