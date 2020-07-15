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
	void PawnKilled(APawn* PawnKilled) override;
};
