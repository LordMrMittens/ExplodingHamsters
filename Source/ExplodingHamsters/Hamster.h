// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HamsterEnums.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Hamster.generated.h"

UCLASS()
class EXPLODINGHAMSTERS_API AHamster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHamster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsPickedUp = false;

	void SetPickedUp(bool _bIsPickedUp);
	UFUNCTION()
	void SetHamsterColour(EHamsterEnums Colour);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    EHamsterEnums HamsterColour;
};
