// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"

#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("GunRoot");
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("GunMesh");
	Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger() {

	// Debug text and camera
	UE_LOG(LogTemp, Warning, TEXT("The trigger has been pulled"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	FVector OwnerLocation;
	FRotator OwnerRotation;
	OwnerController->GetPlayerViewPoint(OwnerLocation, OwnerRotation);

	DrawDebugCamera(GetWorld(), OwnerLocation, OwnerRotation, 90, 1, FColor::Yellow, false, 3.0f);

	// Gun particle effect
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	// Debug line trace
	FVector LinetraceEnd = OwnerLocation + OwnerRotation.Vector() * Range;
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	bool HaveHit = GetWorld()->LineTraceSingleByChannel(HitResult, OwnerLocation, LinetraceEnd, ECollisionChannel::ECC_GameTraceChannel1, Params);
	
	if (HaveHit) {
		DrawDebugPoint(GetWorld(), HitResult.Location, 10, FColor::Red, false, 3.0f);

		// Spawn hit surface particle effect
		FVector ShootDirection = -OwnerRotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), 
			BulletHitFlash, 
			HitResult.Location, 
			ShootDirection.Rotation()
		);

		// Inflict damage
		AActor* HitActor = HitResult.GetActor();
		if (HitActor) {
			FDamageEvent PointDamageEvent = FPointDamageEvent(Damage, HitResult, ShootDirection, NULL);
			HitActor->TakeDamage(Damage, PointDamageEvent, OwnerController, this);
		}
	}


}

