// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class UNREALFPS_API AGun : public AActor
{
	GENERATED_BODY()

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	public:	
		// Sets default values for this actor's properties
		AGun();
		// Called every frame
		virtual void Tick(float DeltaTime) override;

		void PullTrigger();

	private:
		UPROPERTY(VisibleAnywhere)
			USceneComponent* Root;
		UPROPERTY(VisibleAnywhere)
			USkeletalMeshComponent* Mesh;
		UPROPERTY(EditAnywhere)
			UParticleSystem* MuzzleFlash;
		UPROPERTY(EditAnywhere)
			UParticleSystem* BulletHitFlash;
		UPROPERTY(EditAnywhere)
			float Range = 10000.0f;

};
