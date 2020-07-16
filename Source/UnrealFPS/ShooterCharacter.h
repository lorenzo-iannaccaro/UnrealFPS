// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class UNREALFPS_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this character's properties
	AShooterCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Shoot();

	UFUNCTION(BlueprintPure)
		bool IsDead() const;

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AGun> GunClass;

	UPROPERTY()
		AGun* Gun;

	UPROPERTY(EditAnywhere)
	float RotationRate = 50.0f;

	UPROPERTY(VisibleAnywhere)
		float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
		float CurrentHealth;

	void MoveForward(float AxisValue);
	void LookUp(float AxisValue);
	void MoveRight(float AxisValue);
	void LookRight(float AxisValue);

	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

};
