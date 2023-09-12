// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthRegenBuff.h"
#include "HealthComponent.h"
#include "PlayerCharacter.h"

void UHealthRegenBuff::ApplyBuff()
{
	Super::ApplyBuff();
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UHealthRegenBuff::ApplyHealthRegen, TimeDelay, true);
}

void UHealthRegenBuff::RemoveBuff()
{
	Super::RemoveBuff();

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void UHealthRegenBuff::ApplyHealthRegen()
{
	if (HealthComponent == nullptr)
	{
		UHealthComponent* HealthComp = PlayerCharacter->FindComponentByClass<UHealthComponent>();
		if (HealthComp == nullptr)
		{
			return;
		}

		HealthComponent = HealthComp;
	}

	HealthComponent->RestoreHealth(HealthToRegen);
}
