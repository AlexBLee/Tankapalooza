// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buff.h"
#include "ReducedDamageBuff.generated.h"

UCLASS()
class TOONTANKS_API UReducedDamageBuff : public UBuff
{
	GENERATED_BODY()
	
	virtual void ApplyBuff() override;
	virtual void RemoveBuff() override;

	UPROPERTY(EditAnywhere)
	float PercentDamageReduction;
};
