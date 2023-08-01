// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class EXPLODINGHAMSTERS_API UEndScreenWidget : public UUserWidget
{
	GENERATED_BODY()

	protected:
    virtual void NativeConstruct() override;

	public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableText* NameInputText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ContinueButton;

	UFUNCTION()
	void OnButtonWasClicked();


	
};
