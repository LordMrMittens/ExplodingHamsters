// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HighScoresWidget.generated.h"

/**
 *
 */
UCLASS()
class EXPLODINGHAMSTERS_API UHighScoresWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void PopulateHighScores(TArray<struct FScoreStruct> AllScores);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock *ScoresText;
};
