// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CountdownWidget.generated.h"

/**
 * 
 */
UCLASS()
class EXPLODINGHAMSTERS_API UCountdownWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	int32 TimeRemainingText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class AExplosive *  ExplodingHamster;
	
};
