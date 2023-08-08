// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"
#include "HighScoreSaveGame.h"
#include "ScoreStruct.h"
#include "Kismet/GameplayStatics.h"


TArray<FScoreStruct> AMainMenuGameMode::RetrieveHighScores()
{
    UHighScoreSaveGame *SaveGameInstance = Cast<UHighScoreSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("HighScoresSaveSlot"), 0));
        if (!SaveGameInstance)
        {
            SaveGameInstance = Cast<UHighScoreSaveGame>(UGameplayStatics::CreateSaveGameObject(UHighScoreSaveGame::StaticClass()));
            SaveGameInstance->HighScores.Empty();
        }
    return SaveGameInstance->HighScores;
    
}

FText AMainMenuGameMode::PopulateHighScores()
{
    TArray<FText> ScoreEntries;
    int32 index = 1;
    TArray<FScoreStruct> AllScores= RetrieveHighScores();
    if(AllScores.Num()<=0){
        return FText::FromString("No High Scores");
    }
    for (FScoreStruct Score : AllScores)
    {
        FString ScoreString = FString::Printf(TEXT("%d: %s - %d"), index, *Score.ScoreName, Score.RecordedScore);
        ScoreEntries.Add(FText::FromString(ScoreString));
        index++;
    }
    FText ScoreList = FText::Join(FText::FromString("\n"), ScoreEntries);
    return ScoreList;
}
