// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayOptionsScruct.generated.h"

USTRUCT(BlueprintType)
struct EXPLODINGHAMSTERS_API FGameplayOptionsScruct
{

GENERATED_BODY()

public:
	FGameplayOptionsScruct();

UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float HamsterExplosionDelay;
UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MaxHamsterSpawnFrequency;
UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MinHamsterSpawnFrequency;
UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 MaxHamstersInBox;

};
