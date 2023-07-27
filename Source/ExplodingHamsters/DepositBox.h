// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HamsterEnums.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DepositBox.generated.h"

class UDepositBoxTrigger;
class AExplodingHamstersGM;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EHamsterEnums BoxColour;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxHamsters = 10;

		UFUNCTION()
	void OnGameIsOver();

private:
	UPROPERTY()
	AExplodingHamstersGM *ExplodingHamstersGameMode;
	UPROPERTY(EditAnywhere, Category = "Deposit Box")
	UDepositBoxTrigger *DepositBoxTrigger;
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector MovementVelocity;
	FVector StartingLocation;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementDistance;

	UFUNCTION()
	void OnDepositBoxIsFull(ADepositBox *DepositBox);

	void UpdateScore();

	bool bBoxIsEmptying;
	bool bBoxIsMoving;
	bool bBoxIsReturning;

	void MoveBox();
	void GameOverCount();

	FTimerHandle GameOverTimerHandle;
	UPROPERTY(EditAnywhere)
	float GameOverDelay = .5f;

	void StartReturnMovement();
	float ReturnMovementDelay = 2.0f;


};
