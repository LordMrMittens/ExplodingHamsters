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
	
	UPROPERTY(EditAnywhere)
	int32 NumberOfScores = 10;

	

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ScoresText;
	
	TArray<UTextBlock> AllTexts;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TSubclassOf<UTextBlock> TextBlockClass;
	
};
