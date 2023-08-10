// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Hamster.h"
#include "HamAIController.h"
#include "ExplodingHamstersGM.h"
#include "EHPlayerController.h"
#include "PauseMenuWidget.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	    AExplodingHamstersGM* GameMode = Cast<AExplodingHamstersGM>(GetWorld()->GetAuthGameMode());
        if (GameMode)
    {
        GameMode->BoxStartedMoving.AddDynamic(this, &APlayerPawn::OnBoxIsMoving);
        GameMode->BoxCompletedMovement.AddDynamic(this, &APlayerPawn::OnBoxStopped);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Gamemode is null pointer"));
    }
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;
	}
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerPawn::OnPlayerClicked()
{
	if(bCanPickUp){
	FHitResult ObjectHit;
	if (PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, ObjectHit))
	{
		AActor* HamsterActor = ObjectHit.GetActor();
		if (HamsterActor != nullptr && HamsterActor->ActorHasTag("Hamster"))
		{
			AHamster *Hamster = Cast<AHamster>(HamsterActor);
			if (Hamster != nullptr && Hamster->bIsPickedUp == false && Hamster->bIsInBox == false)
			{
				VerticalHoldPosition = HamsterActor->GetActorLocation().Z+50;
				Hamster->SetPickedUp(true);
				HeldHamster = HamsterActor;
			}
			
		}
	}}
}
void APlayerPawn::DragHamster()
{
	if(bCanPickUp==false){
		Release();
	}
	if (HeldHamster != nullptr)
	{
		FVector MouseLocation;
		FVector MouseDirection;
		if (GetMouseWorldPosition(MouseLocation, MouseDirection))
		{
			FVector TraceStart = MouseLocation;
			FVector TraceEnd = MouseLocation + MouseDirection * 10000.0f;
			float DeltaTime = GetWorld()->GetDeltaSeconds();
			FHitResult HitResult;
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(this);
			Params.AddIgnoredActor(HeldHamster);
			if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, Params))
			{
				float VerticalOffset = 40.f; // what is the vertical offset
				FVector Destination(HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z + VerticalOffset);

				FVector NewLocation = FMath::VInterpTo(HeldHamster->GetActorLocation(), Destination, DeltaTime, DraggingSpeed);
				HeldHamster->SetActorLocation(NewLocation);
			}
		}
	}
}

void APlayerPawn::Release()
{
	if(HeldHamster != nullptr){
	 Cast<AHamster>(HeldHamster)->SetPickedUp(false);
	 HeldHamster = nullptr;
	}
}

bool APlayerPawn::GetMouseWorldPosition(FVector &OutMouseLocation, FVector &OutMouseDirection)
{
	if (PlayerController == nullptr)
	{
		return false;
	}

	FViewport *Viewport = CastChecked<ULocalPlayer>(PlayerController->Player)->ViewportClient->Viewport;
	FVector2D MousePosition;
	if (!PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y))
	{
		return false;
	}

	FVector MouseLocation, MouseDirection;
	if (!UGameplayStatics::DeprojectScreenToWorld(PlayerController, MousePosition, MouseLocation, MouseDirection))
	{
		return false;
	}

	OutMouseLocation = MouseLocation;
	OutMouseDirection = MouseDirection;

	return true;
}

void APlayerPawn::TogglePause()
{
	UE_LOG(LogTemp, Error, TEXT("Paused"));
	AEHPlayerController *EHPlayerController = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (EHPlayerController)
	{
		if (EHPlayerController->IsPaused())
		{
			EHPlayerController->HidePanel(EHPlayerController->PauseMenuWidget);
			EHPlayerController->SetPause(false);
		} else {
			EHPlayerController->ShowPanel(EHPlayerController->PauseMenuWidget);
			EHPlayerController->SetPause(true);
			
		}
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	auto eiSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
    //Add the input mapping context
    eiSubsystem->AddMappingContext(InputMapping, 0);
 
    // Get the EnhancedInputComponent
    auto playerEIcomponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//Bind Move() to the mapping
	//BindAction for enhanced system takes Action, ETriggerEvent, object, and function
	//ETriggerEvent is an enum, where Triggered means "button is held down".
	playerEIcomponent->BindAction(InputRightClick, ETriggerEvent::Started, this,  &APlayerPawn::OnPlayerClicked);
	playerEIcomponent->BindAction(InputRightClick, ETriggerEvent::Triggered, this,  &APlayerPawn::DragHamster);
	playerEIcomponent->BindAction(InputRightClick, ETriggerEvent::Completed, this,  &APlayerPawn::Release);
	playerEIcomponent->BindAction(InputPause, ETriggerEvent::Started, this, &APlayerPawn::TogglePause);
}

void APlayerPawn::OnBoxIsMoving()
{
	bCanPickUp = false;
}

void APlayerPawn::OnBoxStopped()
{
	bCanPickUp = true;
}

