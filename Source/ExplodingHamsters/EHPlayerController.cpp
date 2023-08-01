// Fill out your copyright notice in the Description page of Project Settings.

#include "EHPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "ScoreWidget.h"
#include "HighScoresWidget.h"

void AEHPlayerController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Error, TEXT("PlayerController is Alive"));
    ScoreWidget = Cast<UScoreWidget>(CreateWidget(this, ScoreWidgetClass, FName("ScoreWidget")));

    BigScoreWidget = Cast<UScoreWidget>(CreateWidget(this, BigScoreWidgetClass, FName("BigScoreWidget")));

    HighScoreList = Cast<UHighScoresWidget>(CreateWidget(this, HighScoreWidgetClass, FName("HighScoreWidget")));

    if (ScoreWidget != nullptr)
    {
        ScoreWidget->AddToViewport(0);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("No UI Created"));
    }
}

void AEHPlayerController::ShowPanel(UUserWidget* _Panel)
{
    if(_Panel!=nullptr){
        _Panel->AddToViewport(0);
    }
}

void AEHPlayerController::HidePanel(UUserWidget* _Panel)
{
        if(_Panel!=nullptr){
        _Panel->RemoveFromParent();
    }
}
