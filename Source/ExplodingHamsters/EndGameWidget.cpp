// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "EHPlayerController.h"
#include "ExplodingHamstersGM.h"
#include "Kismet/GameplayStatics.h"
#include "Components/EditableTextBox.h"


void UEndGameWidget::SetupWidgetButton()
{
    if(ContinueButton!= nullptr){
        ContinueButton->OnClicked.AddDynamic(this, &UEndGameWidget::OnButtonClicked);
    } else{
        UE_LOG(LogTemp, Error, TEXT("Button is null"));
    }
    AExplodingHamstersGM* GameMode = Cast<AExplodingHamstersGM>(UGameplayStatics::GetGameMode(GetWorld()));
    FString Score = FString::Printf( TEXT("%d"), GameMode->CurrentScore);
    ScoreText->SetText(FText::FromString(Score));
}

void UEndGameWidget::OnButtonClicked()
{
    AEHPlayerController* PlayerController  = Cast<AEHPlayerController>(GetOwningPlayer());
    if(PlayerController != nullptr && ScoreName!= nullptr){
        PlayerController->UpdateHighScores(ScoreName->GetText());
    }
}
