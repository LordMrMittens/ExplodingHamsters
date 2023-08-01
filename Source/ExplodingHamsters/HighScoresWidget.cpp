// Fill out your copyright notice in the Description page of Project Settings.


#include "HighScoresWidget.h"
#include "Components/TextBlock.h"
#include "ScoreWidget.h"
#include "ScoreStruct.h"



void UHighScoresWidget::PopulateHighScores(TArray<FScoreStruct> AllScores)
{
    if(ScoresText!= nullptr){
    FString Scores = "HIGH SCORES\n\n\n";
    int32 index = 1;
    for (FScoreStruct Score : AllScores)
    {
        FString ScoreToAdd =  FString::Printf(TEXT("%d: %s - %d \n"), index, *Score.ScoreName ,Score.RecordedScore);
        index++;
        Scores += ScoreToAdd;
    }
    
        ScoresText->SetText(FText::FromString(Scores));
    } else {
        UE_LOG(LogTemp, Error, TEXT("ScoreTextIsNull"));
    }
    
}
