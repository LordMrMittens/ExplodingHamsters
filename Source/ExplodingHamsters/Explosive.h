// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hamster.h"
#include "GameFramework/Character.h"
#include "Explosive.generated.h"


UCLASS()
class EXPLODINGHAMSTERS_API AExplosive : public AHamster
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AExplosive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Explode();
	void StartExploding();
	
	UFUNCTION()
	void OnBoxIsMoving();
	UFUNCTION()
	void OnBoxStopped();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

UPROPERTY(EditAnywhere)

	float ExplosionTime = 10;
private:
	FTimerHandle ExplosionTimerHandle;

	class AExplodingHamstersGM* GameMode;

	UPROPERTY(EditAnywhere, Category = "Explosion Feedcback")
	float FeedbackFrequency;

	UPROPERTY(EditAnywhere, Category = "Explosion Feedcback")
	float MaxScale;
		UPROPERTY(EditAnywhere, Category = "Explosion Feedcback")
	float DisplaySecondsBeforeExplosion  =5.f;

	float OriginalScale; //this is always the original scale

	float CurrentScale;

	float TimeElapsed;

	bool IsCloseToExploding();

	void ShowExplosionFeedback();

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* ExplosionEffects;
};
