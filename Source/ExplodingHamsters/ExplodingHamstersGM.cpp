// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplodingHamstersGM.h"
#include "ScoreWidget.h"
#include "EHPlayerController.h"
#include "Kismet/GameplayStatics.h"


AExplodingHamstersGM::AExplodingHamstersGM()
{
    PrimaryActorTick.bCanEverTick = true;
}
void AExplodingHamstersGM::BeginPlay()
{
    Super::BeginPlay();
}

void AExplodingHamstersGM::CheckPlayerReferences()
{
        if (PlayerController == nullptr)
    {
        PlayerController = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    }
    if (ScoreWidget == nullptr)
    {
        if (PlayerController->ScoreWidget != nullptr)
        {
            ScoreWidget = PlayerController->ScoreWidget;
            UpdateScore(Score);
        }
    }
}
void AExplodingHamstersGM::Tick(float DeltaTime)
{
    CheckPlayerReferences();

    if (Score < CurrentScore)
    {
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
    if (ScoreWidget != nullptr)
    {
        FString ScoreText = FString::Printf(TEXT("Score: %d"), Score);
        ScoreWidget->UpdateTextBlock(FText::FromString(ScoreText));
    }
}

void AExplodingHamstersGM::ABoxIsMoving()
{
    BoxStartedMoving.Broadcast();
}

void AExplodingHamstersGM::ABoxCompleted()
{
    BoxCompletedMovement.Broadcast();
}
