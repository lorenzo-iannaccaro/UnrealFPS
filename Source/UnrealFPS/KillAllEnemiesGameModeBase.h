// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealFPSGameModeBase.h"
#include "KillAllEnemiesGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREALFPS_API AKillAllEnemiesGameModeBase : public AUnrealFPSGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
	int GetRemainingEnemiesNumber();

	void PawnKilled(APawn* PawnKilled) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AShooterAIController> ShooterAIControllerClass;

	int EnemiesCount;

	void UpdateEnemiesCount();

	void EndGame(bool IsPlayerWinner);
};
