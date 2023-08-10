// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class EXPLODINGHAMSTERS_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetupPauseMenuWidget();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ContinueButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* MenuButton;

	UFUNCTION()
	void LoadMainMenu();
	UFUNCTION()
	void ReturnToGame();
	
};
