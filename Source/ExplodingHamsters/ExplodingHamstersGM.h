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
	void UpdateHighScores(FText _ScoreName);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring")
	class UScoreWidget *ScoreWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring")
	UScoreWidget *BigScoreWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring")
	class UEndScreenWidget *EndScreenWidget;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring")
	class UHighScoresWidget *HighScoresWidget;

	UPROPERTY()
	class AEHPlayerController *PlayerController;

	UPROPERTY(BlueprintAssignable)
	FABoxIsMoving BoxStartedMoving;
	UPROPERTY(BlueprintAssignable)
	FABoxCompletedMovement BoxCompletedMovement;
	UPROPERTY(BlueprintAssignable)
	FGameIsOver OnGameOver;

protected:
	virtual void BeginPlay() override;

private:
	void CheckPlayerReferences();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UHighScoreSaveGame> SaveGameClass;

	UPROPERTY(VisibleAnywhere)
	TArray<struct FScoreStruct> HighScores;

	
	void GetHighScores();

	UPROPERTY(EditAnywhere);
	float EndOfGameLogicDela = 5;

	void EndOfGameSequence();
	

	
};
