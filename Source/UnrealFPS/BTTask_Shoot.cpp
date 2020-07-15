// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "ShooterAIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot() {
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter> (OwnerComp.GetAIOwner()->GetPawn());
	ShooterCharacter->Shoot();

	return EBTNodeResult::Succeeded;
}