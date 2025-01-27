// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALFPS_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

public:
	AShooterAIController();

	virtual void Tick(float DeltaTime) override;

	void FocusAndChase();

	bool IsControlledPawnDead() const;

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly)
	float ChaseRadius = 400.0f;

	APawn* PlayerPawn = nullptr;

	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTree;
	
};
