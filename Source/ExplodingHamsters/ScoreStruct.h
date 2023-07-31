// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScoreStruct.generated.h"

USTRUCT(BlueprintType)
struct EXPLODINGHAMSTERS_API FScoreStruct
{

	GENERATED_BODY()


public:
	FScoreStruct();

UPROPERTY(VisibleAnywhere)
	FString ScoreName;
	UPROPERTY(VisibleAnywhere)
	int32 RecordedScore;
};
