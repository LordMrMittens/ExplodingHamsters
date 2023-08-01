// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class EXPLODINGHAMSTERS_API UEndGameWidget : public UUserWidget
{
	GENERATED_BODY()

		 
	public:
	void SetupWidgetButton();
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ScoreText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ContinueButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* ScoreName;

	UFUNCTION()
	void OnButtonClicked();
	
};
