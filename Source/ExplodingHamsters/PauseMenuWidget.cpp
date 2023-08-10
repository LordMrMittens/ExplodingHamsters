// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidget.h"
#include "Components/Button.h"
#include "EHPlayerController.h"
#include "Kismet/GameplayStatics.h"


void UPauseMenuWidget::SetupPauseMenuWidget()
{
    
    if(ContinueButton != nullptr){
        ContinueButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::ReturnToGame);
        UE_LOG(LogTemp, Error, TEXT("Setting Up ContinueButton"));
    } 
    if(MenuButton != nullptr){
        MenuButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::LoadMainMenu);
        UE_LOG(LogTemp, Error, TEXT("Setting Up menuButton"));
    }
}

void UPauseMenuWidget::LoadMainMenu()
{
        AEHPlayerController *EHPlayerController = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (EHPlayerController)
    {
        UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenu"));
    }
}

void UPauseMenuWidget::ReturnToGame()
{
    AEHPlayerController *EHPlayerController = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (EHPlayerController)
    {
        EHPlayerController->HidePanel(EHPlayerController->PauseMenuWidget);
        EHPlayerController->SetPause(false);
    }
}
