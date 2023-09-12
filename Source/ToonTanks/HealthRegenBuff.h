// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buff.h"
#include "HealthRegenBuff.generated.h"

class UHealthComponent;

UCLASS()
class TOONTANKS_API UHealthRegenBuff : public UBuff
{
	GENERATED_BODY()
	
	virtual void ApplyBuff() override;
	virtual void RemoveBuff() override;

	void ApplyHealthRegen();
	
	UPROPERTY(EditAnywhere)
	float HealthToRegen;

	UPROPERTY(EditAnywhere)
	float TimeDelay;

	UPROPERTY()
	UHealthComponent* HealthComponent;
	
	FTimerHandle TimerHandle;
};
