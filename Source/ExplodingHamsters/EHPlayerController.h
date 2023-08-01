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
	class UScoreWidget* ScoreWidget;
	UScoreWidget* BigScoreWidget;
	class UHighScoresWidget* HighScoresWidget;
	class UEndScreenWidget* EndScreenWidget;

	void ShowPanel(UUserWidget* _PanelToShow);
	void HidePanel(UUserWidget* _PanelToHide);
	

	protected:
	virtual void BeginPlay() override;

	private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UScoreWidget> ScoreWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UScoreWidget> BigScoreWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UEndScreenWidget> EndScreenWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UHighScoresWidget> HighScoresWidgetClass;

	UFUNCTION()
	void RegisterHighScore();

	
	

	
};
