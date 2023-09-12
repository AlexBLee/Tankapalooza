// Fill out your copyright notice in the Description page of Project Settings.


#include "Buff.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

UBuff::UBuff()
{
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(UObject::GetWorld(), 0));
}

void UBuff::ApplyBuff()
{
	UE_LOG(LogTemp, Warning, TEXT("Buff Added: %s"), *Name);
}

void UBuff::RemoveBuff()
{
}
