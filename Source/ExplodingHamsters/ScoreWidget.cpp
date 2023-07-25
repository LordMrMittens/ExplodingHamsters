// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"
#include "Components/TextBlock.h"


void UScoreWidget::UpdateTextBlock(FText _Score)
{
    if(ScoreText!= nullptr){
        ScoreText->SetText(_Score);
    }
}
