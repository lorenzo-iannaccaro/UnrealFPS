// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay() {
	Super::BeginPlay();

	HUDWidget = CreateWidget(this, HUDClass);
	if (HUDWidget != nullptr) {
		HUDWidget->AddToViewport();
	}
}

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) {
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	UE_LOG(LogTemp, Warning, TEXT("Game has ended"));

	if (HUDWidget != nullptr) {
		HUDWidget->RemoveFromViewport();
	}

	if (bIsWinner) {
		UUserWidget* WinScreenWidget = CreateWidget(this, WinScreenClass);
		if (WinScreenWidget != nullptr) {
			WinScreenWidget->AddToViewport();
		}
	}
	else {
		UUserWidget* LoseScreenWidget = CreateWidget(this, LoseScreenClass);
		if (LoseScreenWidget != nullptr) {
			LoseScreenWidget->AddToViewport();
		}
	}

	GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayerController::RestartLevel, LevelRestartDelay);
}