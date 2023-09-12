// Fill out your copyright notice in the Description page of Project Settings.


#include "ReducedDamageBuff.h"

#include "HealthComponent.h"
#include "PlayerCharacter.h"

void UReducedDamageBuff::ApplyBuff()
{
	Super::ApplyBuff();

	UHealthComponent* HealthComponent = PlayerCharacter->FindComponentByClass<UHealthComponent>();
	if (HealthComponent == nullptr)
	{
		return;
	}
	
	HealthComponent->PercentDamageTaken -= PercentDamageReduction;
}

void UReducedDamageBuff::RemoveBuff()
{
	Super::RemoveBuff();

	UHealthComponent* HealthComponent = PlayerCharacter->FindComponentByClass<UHealthComponent>();
	if (HealthComponent == nullptr)
	{
		return;
	}
	
	HealthComponent->PercentDamageTaken += PercentDamageReduction;
}
