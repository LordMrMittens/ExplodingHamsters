// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplodingHamstersGM.h"


AExplodingHamstersGM::AExplodingHamstersGM()
{
    PrimaryActorTick.bCanEverTick = true;
}
void AExplodingHamstersGM::BeginPlay()
{
    Super::BeginPlay();
}
void AExplodingHamstersGM::Tick(float DeltaTime)
{
    if (Score <CurrentScore){
        Score++;
    }
}

void AExplodingHamstersGM::UpdateScore(int32 _Score)
{
    CurrentScore = _Score;
}


