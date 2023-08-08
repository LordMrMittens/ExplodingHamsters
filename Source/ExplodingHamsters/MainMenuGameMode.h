// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class EXPLODINGHAMSTERS_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	 public:
	
	TArray<struct FScoreStruct> RetrieveHighScores();
	UFUNCTION(BlueprintCallable)
	FText PopulateHighScores();
};
