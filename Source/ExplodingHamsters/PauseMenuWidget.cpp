// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidget.h"
#include "Components/Button.h"


void UPauseMenuWidget::SetupPauseMenuWidget()
{
    
    if(ContinueButton != nullptr){
        ContinueButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::LoadMainMenu);
        UE_LOG(LogTemp, Error, TEXT("Setting Up ContinueButton"));
    } 
    if(MenuButton != nullptr){
        MenuButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::ReturnToGame);
        UE_LOG(LogTemp, Error, TEXT("Setting Up menuButton"));
    }
}

void UPauseMenuWidget::LoadMainMenu()
{
    UE_LOG(LogTemp, Error, TEXT("Loading menu pressed"));
}

void UPauseMenuWidget::ReturnToGame()
{
    UE_LOG(LogTemp, Error, TEXT("Return to game pressed"));
}
