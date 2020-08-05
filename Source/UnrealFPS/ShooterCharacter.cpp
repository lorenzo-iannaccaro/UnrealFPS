// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterCharacter.h"
#include "Gun.h"
#include "ShooterAIController.h"
#include "Components/CapsuleComponent.h"
#include "UnrealFPSGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterPlayerController.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// I must call this also here to prevent the case in which IsDead() is called before BeginPlay()
	CurrentHealth = MaxHealth;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Here I re-do the assignment, because the enemy BP custom MaxHealth value has been updated
	CurrentHealth = MaxHealth;
	
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GunSocket"));
	Gun->SetOwner(this);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AShooterCharacter::LookRight);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);

	PlayerInputComponent->BindAction(TEXT("PullTrigger"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);

	PlayerInputComponent->BindAction(TEXT("PauseGame"), EInputEvent::IE_Pressed, this, &AShooterCharacter::PauseGame);


}

void AShooterCharacter::MoveForward(float AxisValue) {
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::LookUp(float AxisValue) {
	AddControllerPitchInput(AxisValue * MouseRotationRate);
}

void AShooterCharacter::MoveRight(float AxisValue) {
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookRight(float AxisValue) {
	AddControllerYawInput(AxisValue * MouseRotationRate);
}

void AShooterCharacter::LookUpRate(float AxisValue) {
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(float AxisValue) {
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Shoot() {
	Gun->PullTrigger();
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) {
	
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ActualDamage = FMath::Min(CurrentHealth, ActualDamage);

	CurrentHealth -= ActualDamage;
	UE_LOG(LogTemp, Warning, TEXT("Character health: %f"), CurrentHealth);

	if (IsDead()) {
		
		AUnrealFPSGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AUnrealFPSGameModeBase>();
		if (GameMode != nullptr) {
			GameMode->PawnKilled(this);
		}

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}

	return ActualDamage;
}

bool AShooterCharacter::IsDead() const {
	return CurrentHealth <= 0;
}

float AShooterCharacter::GetHealthPercentage() const {
	return CurrentHealth / MaxHealth;
}

void AShooterCharacter::PauseGame() {
	AShooterPlayerController* PlayerController = Cast<AShooterPlayerController>(GetController());
	if (PlayerController != nullptr) {
		PlayerController->PauseGame();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Cannot find player controller"));
	}
}

void AShooterCharacter::ReturnToMainMenu() {
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}

