// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_VisiblePlayerLocation.h"
#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_VisiblePlayerLocation::UBTService_VisiblePlayerLocation() {
	NodeName = TEXT("Update Player Location If In Sight");
}

void UBTService_VisiblePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AShooterAIController* ShooterAIController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
	if (ShooterAIController == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Pointer to shoot ai controller is null"));
		return;
	}

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Pointer to player pawn is null"));
		return;
	}

	if (ShooterAIController->LineOfSightTo(PlayerPawn)) {
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
	}
	else {
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}

}
