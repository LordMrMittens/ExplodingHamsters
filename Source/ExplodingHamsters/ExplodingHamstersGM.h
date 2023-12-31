// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExplodingHamstersGameModeBase.h"
#include "ExplodingHamstersGM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FABoxIsMoving);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FABoxCompletedMovement);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameIsOver);
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
	int32 Score;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scoring")
	int32 CurrentScore;

	void ABoxIsMoving();
	void ABoxCompleted();
	void OnGameIsOver();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring")
	class UScoreWidget *ScoreWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring")
	class UScoreWidget *BigScoreWidget;

	UPROPERTY()
	class AEHPlayerController *PlayerController;

	UPROPERTY(BlueprintAssignable)
	FABoxIsMoving BoxStartedMoving;
	UPROPERTY(BlueprintAssignable)
	FABoxCompletedMovement BoxCompletedMovement;
	UPROPERTY(BlueprintAssignable)
	FGameIsOver OnGameOver;

	UPROPERTY(EditAnywhere)
	class UGameplayOptionsDataAsset* GameplayData;

protected:
	virtual void BeginPlay() override;

private:
	void CheckPlayerReferences();
	UPROPERTY(EditAnywhere)
	TArray<USoundWave*> ScoringSounds;
};
