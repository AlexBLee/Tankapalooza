// Fill out your copyright notice in the Description page of Project Settings.

#include "FierceRoundBuff.h"
#include "PlayerCharacter.h"

void UFierceRoundBuff::ApplyBuff()
{
	Super::ApplyBuff();

	if (PlayerCharacter == nullptr)
	{
		return;
	}

	PlayerCharacter->ChangeProjectileClass(ProjectileClass);
}

void UFierceRoundBuff::RemoveBuff()
{
	Super::RemoveBuff();

	if (PlayerCharacter == nullptr)
	{
		return;
	}

	PlayerCharacter->ChangeProjectileClass(DefaultProjectileClass);
}
