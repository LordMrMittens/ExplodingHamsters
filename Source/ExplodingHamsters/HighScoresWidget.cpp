// Fill out your copyright notice in the Description page of Project Settings.


#include "HighScoresWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "ScoreStruct.h"
#include "EHPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UHighScoresWidget::SetupWidget()
{
    if(MenuButton!=nullptr){
        MenuButton->OnClicked.AddDynamic(this, &UHighScoresWidget::ReturnToMainMenu);
    }
}
void UHighScoresWidget::PopulateHighScores(TArray<struct FScoreStruct> AllScores)
{
    TArray<FText> ScoreEntries;
    ScoreEntries.Add(FText::FromString("HIGH SCORES\n\n\n"));
    int32 index = 1;

    for (FScoreStruct Score : AllScores)
    {
        FString ScoreString = FString::Printf(TEXT("%d: %s - %d"), index, *Score.ScoreName, Score.RecordedScore);
        ScoreEntries.Add(FText::FromString(ScoreString));
        index++;
    }

    FText ScoreList = FText::Join(FText::FromString("\n"), ScoreEntries);
    ScoresText->SetText(ScoreList);
    
}

void UHighScoresWidget::ReturnToMainMenu()
{
            AEHPlayerController *EHPlayerController = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (EHPlayerController)
    {
        UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenu"));
    }
}


