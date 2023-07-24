// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DepositBox.generated.h"

class UDepositBoxTrigger;

UCLASS()
class EXPLODINGHAMSTERS_API ADepositBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADepositBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

UPROPERTY(EditAnywhere, Category="Deposit Box")
UDepositBoxTrigger* DepositBoxTrigger;

	UFUNCTION()
	void OnDepositBoxIsFull(ADepositBox* DepositBox);
};
