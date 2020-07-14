// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

AShooterAIController::AShooterAIController() {

}

void AShooterAIController::BeginPlay() {
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

}

void AShooterAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

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
