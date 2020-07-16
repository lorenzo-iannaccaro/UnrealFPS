// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALFPS_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

private:
	UPROPERTY(EditAnywhere)
	float LevelRestartDelay = 5.0f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> LoseScreenClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> WinScreenClass;

	FTimerHandle TimerHandle;

};
