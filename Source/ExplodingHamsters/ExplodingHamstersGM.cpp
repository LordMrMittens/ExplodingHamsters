// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplodingHamstersGM.h"
#include "ScoreWidget.h"
#include "EHPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayOptionsDataAsset.h"


AExplodingHamstersGM::AExplodingHamstersGM()
{
    PrimaryActorTick.bCanEverTick = true;
}
void AExplodingHamstersGM::BeginPlay()
{
    Super::BeginPlay();
    if(GameplayData == nullptr){
        UE_LOG(LogTemp, Error, TEXT("No Gameplay data present in game mode"));
    }
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
        PlayerController->ShowPanel(PlayerController->BigScoreWidget);
        ScoreUpdatecounter += DeltaTime;
        if (ScoreUpdatecounter > ScoreUpdateSpeed)
        {
            Score++;
            ScoreUpdatecounter = 0.f;
            UpdateScore(0);
            if(ScoringSounds.Num() >0){
                int SoundIndex = FMath::RandRange(0, ScoringSounds.Num()-1);
                UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ScoringSounds[SoundIndex], FVector::ZeroVector);
            }
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
}
