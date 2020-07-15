// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_VisiblePlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class UNREALFPS_API UBTService_VisiblePlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_VisiblePlayerLocation();

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
