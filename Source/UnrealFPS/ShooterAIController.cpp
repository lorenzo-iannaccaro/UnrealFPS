// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

AShooterAIController::AShooterAIController() {

}

void AShooterAIController::BeginPlay() {
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (BehaviorTree != nullptr) {
		RunBehaviorTree(BehaviorTree);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

void AShooterAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

bool AShooterAIController::IsControlledPawnDead() const{
	AShooterCharacter* ControlledPawn = Cast<AShooterCharacter>(GetPawn());
	if (ControlledPawn != nullptr) {
		return ControlledPawn->IsDead();
	}

	return true;	// If cannot find controlled pawn, this counts as dead
}

