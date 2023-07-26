// Fill out your copyright notice in the Description page of Project Settings.


#include "EHPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "ScoreWidget.h"

    void AEHPlayerController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Error, TEXT("PlayerController is Alive"));
    ScoreWidget = Cast<UScoreWidget>(CreateWidget( this, ScoreWidgetClass, FName("Scorewidget")));
    if(ScoreWidget!= nullptr){
        ScoreWidget->AddToViewport(0);
    }else {
        UE_LOG(LogTemp, Error, TEXT("No UI Created"));
    }
}
