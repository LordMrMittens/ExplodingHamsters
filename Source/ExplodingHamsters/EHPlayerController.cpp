// Fill out your copyright notice in the Description page of Project Settings.

#include "EHPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "ScoreWidget.h"
#include "HighScoresWidget.h"
#include "EndScreenWidget.h"

void AEHPlayerController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Error, TEXT("PlayerController is Alive"));
    ScoreWidget = Cast<UScoreWidget>(CreateWidget(this, ScoreWidgetClass, FName("ScoreWidget")));
    BigScoreWidget = Cast<UScoreWidget>(CreateWidget(this, BigScoreWidgetClass, FName("BigScoreWidget")));
    HighScoresWidget = Cast<UHighScoresWidget>(CreateWidget(this, HighScoresWidgetClass, FName("HighScores")));
    EndScreenWidget = Cast<UEndScreenWidget>(CreateWidget(this, EndScreenWidgetClass, FName("EndScreenWidget")));
    ShowPanel(ScoreWidget);
    
}

void AEHPlayerController::RegisterHighScore()
{
    HidePanel(EndScreenWidget);
    ShowPanel(HighScoresWidget);
    
}

void AEHPlayerController::ShowPanel(UUserWidget *_PanelToShow)
{
    if (_PanelToShow != nullptr)
    {
        _PanelToShow->AddToViewport(0);
    }
}

void AEHPlayerController::HidePanel(UUserWidget *_PanelToHide)
{
    if (_PanelToHide != nullptr)
    {
        _PanelToHide->RemoveFromParent();
    }
}
