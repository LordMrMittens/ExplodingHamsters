// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EHPlayerController.generated.h"

/**
 *
 */
UCLASS()
class EXPLODINGHAMSTERS_API AEHPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	class UScoreWidget *ScoreWidget;
	UScoreWidget *BigScoreWidget;
	class UHighScoresWidget *HighScoreList;
	class UEndGameWidget* EndGameWidget;
	void ShowPanel(UUserWidget* _Panel);
	void HidePanel(UUserWidget* _Panel);
	void UpdateHighScores();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UScoreWidget> ScoreWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UScoreWidget> BigScoreWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UEndGameWidget> EndGameWidgetClass;
		UPROPERTY(EditAnywhere)
	TSubclassOf<UHighScoresWidget> HighScoreWidgetClass;

		UPROPERTY(EditAnywhere)
	TSubclassOf<class UHighScoreSaveGame> SaveGameClass;

	UPROPERTY(VisibleAnywhere)
	TArray<struct FScoreStruct> HighScores;

	
	void DisplayGameOverScreen();

	UFUNCTION()
	void OnGameOver();

	FTimerHandle EndDelayHandle;
	
};
