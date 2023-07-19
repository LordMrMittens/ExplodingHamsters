// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckIsGrabbed.h"
#include "Hamster.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_CheckIsGrabbed::UBTService_CheckIsGrabbed(){
        NodeName = "Check If Grabbed";
    bNotifyBecomeRelevant =true;
}

void UBTService_CheckIsGrabbed::OnBecomeRelevant(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::OnBecomeRelevant(OwnerComp, NodeMemory);
    HamPawn = OwnerComp.GetAIOwner()->GetPawn();
    Hamster = Cast<AHamster>(HamPawn);


}

void UBTService_CheckIsGrabbed::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    if(HamPawn!= nullptr){
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), Hamster->bIsPickedUp);
    }
}

