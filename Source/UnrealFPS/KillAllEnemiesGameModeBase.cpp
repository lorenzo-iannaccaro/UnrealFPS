// Fill out your copyright notice in the Description page of Project Settings.

#include "KillAllEnemiesGameModeBase.h"
#include "EngineUtils.h"
#include "ShooterPlayerController.h"

void AKillAllEnemiesGameModeBase::PawnKilled(APawn* PawnKilled) {
	Super::PawnKilled(PawnKilled);

	UE_LOG(LogTemp, Warning, TEXT("%s has been killed."), *PawnKilled->GetName());

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr) {
		EndGame(false);
	}
}

void AKillAllEnemiesGameModeBase::EndGame(bool IsPlayerWinner) {
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		if (Controller->IsPlayerController() == IsPlayerWinner){
			Controller->GameHasEnded(Controller->GetPawn(), true);
		}
		else {
			Controller->GameHasEnded(Controller->GetPawn(), false);
		}
	}
}

