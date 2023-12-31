// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HamsterEnums.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DepositBox.generated.h"

class UDepositBoxTrigger;
class AExplodingHamstersGM;
class ADoor;
class AExplosive;

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
	void SetHamsterSlot(AExplosive* Hamster);
	void ClearHamsterSlots();

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

	TPair<USceneComponent* ,AExplosive*> GetHamsterSlot();

	UFUNCTION()
	void OnDepositBoxIsFull(ADepositBox *DepositBox);

	void UpdateScore();

	bool bBoxIsEmptying;
	bool bBoxIsMoving;
	bool bBoxIsReturning;

	void MoveBox(FVector _MovementVelocity, FVector _StartingPoint);
	void GameOverCount();

	FTimerHandle GameOverTimerHandle;
	UPROPERTY(EditAnywhere)
	float GameOverDelay = .5f;

	void StartReturnMovement();
	float ReturnMovementDelay = 2.0f;

	UPROPERTY(EditAnywhere,Category = "Door" )
	ADoor *Door;

	UPROPERTY(EditAnywhere,Category = "Door")
	FVector DoorOpeningDirection;

	UPROPERTY(EditAnywhere,Category = "Door")
	float DoorOpeningDistance;

	UPROPERTY(EditAnywhere,Category = "Door")
	float DoorMovementSpeed;

	UPROPERTY(EditAnywhere,Category = "Door")
	float CloseDoorDelay;

	TArray<USceneComponent*> HamsterLocations;

	TArray<TPair<USceneComponent* ,AExplosive*>> LocationsTMap;

	UPROPERTY(EditAnywhere)
	class USoundWave* BoxServoSound;

	class UAudioComponent* BoxServoSoundComponent;

	
};
