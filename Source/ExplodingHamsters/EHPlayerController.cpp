// Fill out your copyright notice in the Description page of Project Settings.

#include "EHPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "ScoreWidget.h"
#include "HighScoresWidget.h"
#include "HighScoreSaveGame.h"
#include "ScoreStruct.h"
#include "HighScoresWidget.h"
#include "ExplodingHamstersGM.h"

void AEHPlayerController::BeginPlay()
{
    Super::BeginPlay();
    HighScores.Empty();
    ScoreWidget = Cast<UScoreWidget>(CreateWidget(this, ScoreWidgetClass, FName("ScoreWidget")));

    BigScoreWidget = Cast<UScoreWidget>(CreateWidget(this, BigScoreWidgetClass, FName("BigScoreWidget")));

    HighScoreList = Cast<UHighScoresWidget>(CreateWidget(this, HighScoreWidgetClass, FName("HighScoreWidget")));

    ShowPanel(ScoreWidget);

        AExplodingHamstersGM *GameMode = Cast<AExplodingHamstersGM>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GameMode)
    {
        GameMode->OnGameOver.AddDynamic(this, &AEHPlayerController::OnGameOver);
    }
}

void AEHPlayerController::ShowPanel(UUserWidget *_Panel)
{
    if (_Panel != nullptr)
    {
        _Panel->AddToViewport(0);
    }
}

void AEHPlayerController::HidePanel(UUserWidget *_Panel)
{
    if (_Panel != nullptr)
    {
        _Panel->RemoveFromParent();
    }
}

void AEHPlayerController::UpdateHighScores()
{
    FScoreStruct ThisScore;
    AExplodingHamstersGM *GameMode = Cast<AExplodingHamstersGM>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GameMode)
    {/*
        ThisScore.RecordedScore = GameMode->CurrentScore;
        ThisScore.ScoreName = "Placeholder";
        UHighScoreSaveGame *SaveGameInstance = Cast<UHighScoreSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("HighScoresSaveSlot"), 0));
        if (!SaveGameInstance)
        {
            SaveGameInstance = Cast<UHighScoreSaveGame>(UGameplayStatics::CreateSaveGameObject(UHighScoreSaveGame::StaticClass()));
        }
        HighScores = SaveGameInstance->HighScores;
        
        HighScores.Sort([](const FScoreStruct &A, const FScoreStruct &B)
                        { return A.RecordedScore > B.RecordedScore; });
        const int32 MaxScores = 10;
        if (HighScores.Num() > MaxScores)
        {
            HighScores.RemoveAt(MaxScores, HighScores.Num() - MaxScores, true);
        }
        SaveGameInstance->HighScores = HighScores;
        UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("HighScoresSaveSlot"), 0);
        */
       HighScores.Add(ThisScore);
        if (HighScoreList)
        {
            HighScoreList->PopulateHighScores(HighScores);
            ShowPanel(HighScoreList);
        }
    }
}

void AEHPlayerController::OnGameOver()
{
UpdateHighScores();
}
