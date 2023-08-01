// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplodingHamstersGM.h"
#include "ScoreWidget.h"
#include "EHPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "HighScoreSaveGame.h"
#include "ScoreStruct.h"
#include "HighScoresWidget.h"
#include "EndScreenWidget.h"


AExplodingHamstersGM::AExplodingHamstersGM()
{
    PrimaryActorTick.bCanEverTick = true;
}
void AExplodingHamstersGM::BeginPlay()
{
    Super::BeginPlay();
    GetHighScores();
}

void AExplodingHamstersGM::CheckPlayerReferences()
{
        if (PlayerController == nullptr)
    {
        PlayerController = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    }
    if (ScoreWidget == nullptr || BigScoreWidget == nullptr)
    {
        if (PlayerController->ScoreWidget != nullptr && PlayerController->BigScoreWidget != nullptr)
        {
            ScoreWidget = PlayerController->ScoreWidget;
            BigScoreWidget = PlayerController->BigScoreWidget;
            HighScoresWidget = PlayerController->HighScoresWidget;
            UpdateScore(Score);
        }
    }
}

void AExplodingHamstersGM::Tick(float DeltaTime)
{
    CheckPlayerReferences();

    if (Score < CurrentScore && PlayerController != nullptr)
    {
        PlayerController->ShowPanel(PlayerController->BigScoreWidget);
        ScoreUpdatecounter += DeltaTime;
        if (ScoreUpdatecounter > ScoreUpdateSpeed)
        {
            Score++;
            ScoreUpdatecounter = 0.f;
            UpdateScore(0);
        }
    }
}

void AExplodingHamstersGM::UpdateScore(int32 _Score)
{
    CurrentScore += _Score;
    if (ScoreWidget != nullptr && BigScoreWidget != nullptr)
    {
        FString ScoreText = FString::Printf(TEXT("Score: %d"), Score);
        FString BigScoreTextUI = FString::Printf(TEXT("Hammies Defused: %d"), Score);
        ScoreWidget->UpdateTextBlock(FText::FromString(ScoreText));
        BigScoreWidget->UpdateTextBlock(FText::FromString(BigScoreTextUI));
    }
    
}

void AExplodingHamstersGM::ABoxIsMoving()
{
    BoxStartedMoving.Broadcast();
}

void AExplodingHamstersGM::ABoxCompleted()
{
    PlayerController->HidePanel(PlayerController->BigScoreWidget);
    BoxCompletedMovement.Broadcast();
}

void AExplodingHamstersGM::OnGameIsOver()
{
    OnGameOver.Broadcast();
    FTimerHandle EndOfGameLogicHandle;
    GetWorldTimerManager().SetTimer(EndOfGameLogicHandle, this, &AExplodingHamstersGM::EndOfGameSequence, EndOfGameLogicDela , false);
    
}

void AExplodingHamstersGM::UpdateHighScores(FText _ScoreName)
{
    FScoreStruct ThisScore;
    ThisScore.RecordedScore= this->CurrentScore;
    ThisScore.ScoreName= _ScoreName.ToString();
    UHighScoreSaveGame* SaveGameInstance = Cast<UHighScoreSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("HighScoresSaveSlot"), 0));
    if (!SaveGameInstance)
    {
        SaveGameInstance = Cast<UHighScoreSaveGame>(UGameplayStatics::CreateSaveGameObject(UHighScoreSaveGame::StaticClass()));
    }

    SaveGameInstance->HighScores.Add(ThisScore);
    SaveGameInstance->HighScores.Sort([](const FScoreStruct &A, const FScoreStruct &B)
                                      { return A.RecordedScore > B.RecordedScore; });
    const int32 MaxScores = 10;
    if (SaveGameInstance->HighScores.Num() > MaxScores)
    {
        SaveGameInstance->HighScores.RemoveAt(MaxScores, SaveGameInstance->HighScores.Num() - MaxScores, true);
    }
        UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("HighScoresSaveSlot"), 0);
    PlayerController->HighScoresWidget->PopulateHighScores(HighScores);
}

void AExplodingHamstersGM::GetHighScores()
{
    UHighScoreSaveGame *SaveGameInstance = Cast<UHighScoreSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("HighScoresSaveSlot"), 0));
    if (SaveGameInstance)
    {
        HighScores = SaveGameInstance->HighScores;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("No high scores detected"));
    }
}

void AExplodingHamstersGM::EndOfGameSequence()
{
    //UpdateHighScores();
    GetHighScores();
    PlayerController->ShowPanel(PlayerController->EndScreenWidget);
}
