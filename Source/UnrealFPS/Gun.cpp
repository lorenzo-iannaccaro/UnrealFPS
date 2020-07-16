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

	UE_LOG(LogTemp, Warning, TEXT("The trigger has been pulled"));

	// Get owner controller
	OwnerController = GetOwnerController();
	if (!OwnerController) {
		UE_LOG(LogTemp, Error, TEXT("Gun owner controller not found"));
		return;
	}

	// Get player viewpoint
	FVector OwnerLocation;
	FRotator OwnerRotation;
	OwnerController->GetPlayerViewPoint(OwnerLocation, OwnerRotation);

	// Gun particle effect
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	// Draw debug camera
	DrawDebugCamera(GetWorld(), OwnerLocation, OwnerRotation, 90, 1, FColor::Yellow, false, 3.0f);

	// Do line trace and hit effects
	ProjectileLineTrace(OwnerLocation, OwnerRotation);

}

void AGun::ProjectileLineTrace(FVector& OwnerLocation, FRotator& OwnerRotation)
{
	// Line trace
	FVector LinetraceEnd = OwnerLocation + OwnerRotation.Vector() * Range;
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	bool HaveHit = GetWorld()->LineTraceSingleByChannel(HitResult, OwnerLocation, LinetraceEnd, ECollisionChannel::ECC_GameTraceChannel1, Params);

	// Hit effects
	if (HaveHit) {
		// Draw debug hit point
		DrawDebugPoint(GetWorld(), HitResult.Location, 10, FColor::Red, false, 3.0f);

		// Spawn hit surface particle effect
		FVector ShootDirection = -OwnerRotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
			BulletHitFlash,
			HitResult.Location,
			ShootDirection.Rotation()
		);

		InflictDamage(HitResult, ShootDirection);
	}
}

void AGun::InflictDamage(FHitResult& HitResult, FVector& ShootDirection)
{
	// Inflict damage
	AActor* HitActor = HitResult.GetActor();
	if (HitActor) {
		FDamageEvent PointDamageEvent = FPointDamageEvent(Damage, HitResult, ShootDirection, NULL);
		HitActor->TakeDamage(Damage, PointDamageEvent, OwnerController, this);
	}
}

AController* AGun::GetOwnerController() {
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;
	OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return nullptr;

	return OwnerController;
}

