// Fill out your copyright notice in the Description page of Project Settings.

#include "EndScreenWidget.h"
#include "Components/EditableText.h"
#include "Components/Button.h"
#include "ExplodingHamstersGM.h"
#include "Kismet/GameplayStatics.h"

void UEndScreenWidget::NativeConstruct()
{
    if (ContinueButton != nullptr)
    {
     //   ContinueButton->OnPressed.AddDynamic(this, &UEndScreenWidget::OnButtonWasClicked);
    }
}

void UEndScreenWidget::OnButtonWasClicked()
{
    UE_LOG(LogTemp, Error, TEXT("Button Is Clicked"));
}
