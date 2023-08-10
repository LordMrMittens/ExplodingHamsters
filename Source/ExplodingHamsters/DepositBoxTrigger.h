// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "DepositBoxTrigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDepositBoxIsFullDelegate, ADepositBox *, DepositBox);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EXPLODINGHAMSTERS_API UDepositBoxTrigger : public UBoxComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDepositBoxTrigger();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	class ADepositBox *ThisDepositBox;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	UPROPERTY(VisibleAnywhere)
	TArray<AActor *> ContainedHamsters;
	void ResetDepositBox();
	void DestroyDepositBox();
	void SetupDepositBox(int32 _MaxHamsters, ADepositBox *_DepositBox);

	bool IsValidHamster(AActor *HamsterActor, class AExplosive *&DepositedHamster, bool &ShouldExplode);
	bool bIsDestroyed = false;

	UPROPERTY(BlueprintAssignable, Category = "Deposit Box")
	FDepositBoxIsFullDelegate OnDepositBoxIsFull;

private:
	UPROPERTY(VisibleAnywhere)
	int32 MaxHamsters;
};
