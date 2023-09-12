// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buff.h"
#include "FierceRoundBuff.generated.h"

class AProjectile;

UCLASS()
class TOONTANKS_API UFierceRoundBuff : public UBuff
{
	GENERATED_BODY()

	virtual void ApplyBuff() override;
	virtual void RemoveBuff() override;

	UPROPERTY(EditAnywhere, Category = "Projectiles", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectile> DefaultProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Projectiles", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectile> ProjectileClass;
};
