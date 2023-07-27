// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class EXPLODINGHAMSTERS_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
    class UInputMappingContext* InputMapping;
	    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
    class UInputAction* InputRightClick;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	float DraggingSpeed = 20.0f;
	UFUNCTION()
	void OnBoxIsMoving();
	UFUNCTION()
	void OnBoxStopped();
private:
	APlayerController* PlayerController;
	void OnPlayerClicked();
	float VerticalHoldPosition;
	AActor* HeldHamster;
	void DragHamster();
	void Release();
	bool bCanPickUp = true;

	bool GetMouseWorldPosition(FVector &OutMouseLocation, FVector &OutMouseDirection);

};
