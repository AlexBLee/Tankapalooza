// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class AToonTanksGameMode;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float GetHealth();
	
	UFUNCTION(BlueprintCallable)
	float GetHealthPercentage();

	void RestoreToFullHealth();
	void AddMaxHealth(float HealthToSet);
	void SetDefaultHealth();

	void RestoreHealth(float HealthToSet);

	float PercentDamageTaken = 1;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;

	UPROPERTY(VisibleInstanceOnly)
	float Health = 0.f;
	float DefaultHealth;
	
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser);

	AToonTanksGameMode* ToonTanksGameMode;
};
