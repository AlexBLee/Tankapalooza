// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBuff.h"
#include "HealthComponent.h"
#include "PlayerCharacter.h"

void UHealthBuff::ApplyBuff()
{
	Super::ApplyBuff();

	UHealthComponent* HealthComponent = PlayerCharacter->FindComponentByClass<UHealthComponent>();
	if (HealthComponent == nullptr)
	{
		return;
	}

	HealthComponent->AddMaxHealth(HealthToAdd);
	HealthComponent->RestoreToFullHealth();
}

void UHealthBuff::RemoveBuff()
{
	Super::RemoveBuff();

	UHealthComponent* HealthComponent = PlayerCharacter->FindComponentByClass<UHealthComponent>();
	if (HealthComponent == nullptr)
	{
		return;
	}

	HealthComponent->SetDefaultHealth();
}
