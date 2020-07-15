// Fill out your copyright notice in the Description page of Project Settings.


#include "KillAllEnemiesGameModeBase.h"

void AKillAllEnemiesGameModeBase::PawnKilled(APawn* PawnKilled) {
	Super::PawnKilled(PawnKilled);

	UE_LOG(LogTemp, Warning, TEXT("%s has been killed."), *PawnKilled->GetName());

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr) {
		PlayerController->GameHasEnded(nullptr, false);
	}
}