// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplodingHamstersGM.h"
#include "ScoreWidget.h"
#include "EHPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "HighScoreSaveGame.h"
#include "ScoreStruct.h"


AExplodingHamstersGM::AExplodingHamstersGM()
{
    PrimaryActorTick.bCanEverTick = true;
}
void AExplodingHamstersGM::BeginPlay()
{
    Super::BeginPlay();
    GetHighScores();
    bShouldRecordNewHighScore = true;
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
            UpdateScore(Score);
        }
    }
}

void AExplodingHamstersGM::Tick(float DeltaTime)
{
    CheckPlayerReferences();

    if (Score < CurrentScore && PlayerController != nullptr)
    {
        PlayerController->ShowScoreUpdatePanel();
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
    PlayerController->HideScoreUpdatePanel();
    BoxCompletedMovement.Broadcast();
    if( bHasGameEnded){
        UpdateHighScores();
    }
}

void AExplodingHamstersGM::OnGameIsOver()
{
    OnGameOver.Broadcast();
    bHasGameEnded = true;
    
}

void AExplodingHamstersGM::UpdateHighScores()
{
        if (bShouldRecordNewHighScore == true)
    {
    FScoreStruct ThisScore;
    ThisScore.RecordedScore= this->CurrentScore;
    ThisScore.ScoreName= "Placeholder";
    UHighScoreSaveGame* SaveGameInstance = Cast<UHighScoreSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("HighScoresSaveSlot"), 0));
    if (!SaveGameInstance)
    {
        SaveGameInstance = Cast<UHighScoreSaveGame>(UGameplayStatics::CreateSaveGameObject(UHighScoreSaveGame::StaticClass()));
    }
    SaveGameInstance->HighScores.Add(ThisScore);

    SaveGameInstance->HighScores.Sort([](const FScoreStruct &A, const FScoreStruct &B)
                                      { return A.RecordedScore > B.RecordedScore; });

    // Ensure that the HighScores array has a maximum of 10 scores
    const int32 MaxScores = 10;
    if (SaveGameInstance->HighScores.Num() > MaxScores)
    {
        SaveGameInstance->HighScores.RemoveAt(MaxScores, SaveGameInstance->HighScores.Num() - MaxScores, true);
    }

    for (auto AScore : SaveGameInstance->HighScores)
    {
        UE_LOG(LogTemp, Error, TEXT("Reading off instance name :%s, Score: %d"), *AScore.ScoreName, AScore.RecordedScore);
    }

        UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("HighScoresSaveSlot"), 0);
        bShouldRecordNewHighScore = false;
    }
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
