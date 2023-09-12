// Fill out your copyright notice in the Description page of Project Settings.


#include "HatBuff.h"
#include "PlayerCharacter.h"

void UHatBuff::ApplyBuff()
{
	Super::ApplyBuff();

	if (PlayerCharacter == nullptr)
	{
		return;
	}

	PlayerCharacter->SetHatMesh(Hat);
}

void UHatBuff::RemoveBuff()
{
	Super::RemoveBuff();

	if (PlayerCharacter == nullptr)
	{
		return;
	}

	PlayerCharacter->SetHatMesh(nullptr);
}
