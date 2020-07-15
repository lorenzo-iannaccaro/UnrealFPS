// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) {
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	UE_LOG(LogTemp, Warning, TEXT("Game has ended"));

	UUserWidget* LoseScreenWidget = CreateWidget(this, LoseScreenClass);
	if (LoseScreenWidget != nullptr) {
		LoseScreenWidget->AddToViewport();
	}

	GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayerController::RestartLevel, LevelRestartDelay);
}