// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameWidget.h"
#include "Components/Button.h"
#include "EHPlayerController.h"


void UEndGameWidget::SetupWidgetButton()
{
    if(ContinueButton!= nullptr){
        ContinueButton->OnClicked.AddDynamic(this, &UEndGameWidget::OnButtonClicked);
    } else{
        UE_LOG(LogTemp, Error, TEXT("Button is null"));
    }
}

void UEndGameWidget::OnButtonClicked()
{
    UE_LOG(LogTemp, Display, TEXT("Button Pressed"));
    AEHPlayerController* PlayerController  = Cast<AEHPlayerController>(GetOwningPlayer());
    if(PlayerController != nullptr){
        PlayerController->UpdateHighScores();
    }
}
