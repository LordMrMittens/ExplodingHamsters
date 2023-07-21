// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckInBox.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Hamster.h"


UBTService_CheckInBox::UBTService_CheckInBox()
{
            NodeName = "Check If In Box";
    bNotifyBecomeRelevant =true;
}

void UBTService_CheckInBox::OnBecomeRelevant(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
}

void UBTService_CheckInBox::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    Hamster = Cast<AHamster>(OwnerComp.GetAIOwner()->GetPawn());
    if (Hamster != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("AI %s, is possessing< %s"), *OwnerComp.GetAIOwner()->GetActorNameOrLabel(), *Hamster->GetActorNameOrLabel());

        OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), Hamster->bIsInBox);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("null"));
    }
}
