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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scoring")
	int32 Score = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scoring")
	int32 CurrentScore = 0;

protected:
	virtual void BeginPlay() override;

private:
};
