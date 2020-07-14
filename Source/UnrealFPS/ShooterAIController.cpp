// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AShooterAIController::AShooterAIController() {

}

void AShooterAIController::BeginPlay() {
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (BehaviorTree != nullptr) {
		RunBehaviorTree(BehaviorTree);
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

void AShooterAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	//FocusAndChase();

}

void AShooterAIController::FocusAndChase()
{
	if (PlayerPawn != nullptr) {

		if (LineOfSightTo(PlayerPawn)) {
			SetFocus(PlayerPawn);
			MoveToActor(PlayerPawn, ChaseRadius);
		}
		else {
			ClearFocus(EAIFocusPriority::LastFocusPriority);
			StopMovement();
		}

	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Player pawn not found"));
	}
}
