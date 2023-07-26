// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExplodingHamstersGameModeBase.h"
#include "ExplodingHamstersGM.generated.h"

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


UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring")
	class UScoreWidget* ScoreWidget;

	UPROPERTY()
	class AEHPlayerController* PlayerController;

protected:
	virtual void BeginPlay() override;

private:


 
};
