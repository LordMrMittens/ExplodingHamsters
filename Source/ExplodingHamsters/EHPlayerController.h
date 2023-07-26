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
	protected:
	virtual void BeginPlay() override;

	private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UScoreWidget> ScoreWidgetClass;
	

	
};
