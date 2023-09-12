// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buff.h"
#include "HealthBuff.generated.h"

UCLASS(Blueprintable)
class TOONTANKS_API UHealthBuff : public UBuff
{
	GENERATED_BODY()

	virtual void ApplyBuff() override;
	virtual void RemoveBuff() override;

	UPROPERTY(EditAnywhere)
	float HealthToAdd;
};
