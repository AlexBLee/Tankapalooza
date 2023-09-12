// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_IsInRange.generated.h"

class ABaseCharacter;

UCLASS()
class TOONTANKS_API UBTService_IsInRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	UBTService_IsInRange();

public:
	UPROPERTY(EditAnywhere)
	float MaximumDistance;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
