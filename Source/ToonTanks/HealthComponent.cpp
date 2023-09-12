// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	DefaultHealth = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
}

float UHealthComponent::GetHealth()
{
	return Health;
}

float UHealthComponent::GetHealthPercentage()
{
	return Health / MaxHealth;
}

void UHealthComponent::RestoreToFullHealth()
{
	Health = MaxHealth;
}

void UHealthComponent::SetDefaultHealth()
{
	Health = DefaultHealth;
}

void UHealthComponent::RestoreHealth(float HealthToSet)
{
	if (Health >= MaxHealth)
	{
		return;
	}
	
	Health += HealthToSet;
}

void UHealthComponent::AddMaxHealth(float HealthToSet)
{
	MaxHealth += HealthToSet;
}

void UHealthComponent::DamageTaken(AActor *DamagedActor, float Damage, const UDamageType *DamageType, AController *Instigator, AActor *DamageCauser)
{
	if (Damage <= 0.f)
	{
		return;
	}

	Health -= Damage * PercentDamageTaken;

	if (Health <= 0.f && ToonTanksGameMode)
	{
		ToonTanksGameMode->ActorDied(DamagedActor);
	}
}



