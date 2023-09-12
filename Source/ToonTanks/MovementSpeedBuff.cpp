// Fill out your copyright notice in the Description page of Project Settings.

#include "MovementSpeedBuff.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMovementSpeedBuff::ApplyBuff()
{
	Super::ApplyBuff();

	UCharacterMovementComponent* MovementComponent = PlayerCharacter->FindComponentByClass<UCharacterMovementComponent>();
	if (MovementComponent == nullptr)
	{
		return;
	}
	
	MovementComponent->MaxWalkSpeed += MovementSpeedToAdd;
}

void UMovementSpeedBuff::RemoveBuff()
{
	Super::RemoveBuff();

	UCharacterMovementComponent* MovementComponent = PlayerCharacter->FindComponentByClass<UCharacterMovementComponent>();
	if (MovementComponent == nullptr)
	{
		return;
	}

	MovementComponent->MaxWalkSpeed -= MovementSpeedToAdd;
}
