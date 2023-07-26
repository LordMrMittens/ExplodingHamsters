// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExplodingHamstersGameModeBase.h"
#include "ExplodingHamstersGM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FABoxIsMoving);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FABoxCompletedMovement);
/**
 *
 */
UCLASS()
class EXPLODINGHAMSTERS_API AExplodingHamstersGM : public AExplodingHamstersGameModeBase
{
	GENERATED_BODY()

public:
	AExplodingHamstersGM();
	virtual void Tick(float DeltaTime) override;
	void UpdateScore(int32 _Score);

	UPROPERTY(EditAnywhere, Category = "Scoring")
	float ScoreUpdateSpeed = .1f;
	float ScoreUpdatecounter = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Scoring")
	int32 Score = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scoring")
	int32 CurrentScore = 0;

	void ABoxIsMoving();
	void ABoxCompleted();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring")
	class UScoreWidget *ScoreWidget;

	UPROPERTY()
	class AEHPlayerController *PlayerController;

	UPROPERTY(BlueprintAssignable)
	FABoxIsMoving BoxStartedMoving;
	UPROPERTY(BlueprintAssignable)
	FABoxCompletedMovement BoxCompletedMovement;

protected:
	virtual void BeginPlay() override;

private:
	void CheckPlayerReferences();
};
