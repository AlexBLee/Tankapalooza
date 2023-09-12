// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buff.generated.h"

class APlayerCharacter;

UCLASS(Blueprintable)
class TOONTANKS_API UBuff : public UObject
{
	GENERATED_BODY()
	
public:
	UBuff();

public:
	virtual void ApplyBuff();
	virtual void RemoveBuff();

	FString GetBuffName() const { return Name; }
	bool IsStackable() const { return bIsStackable; }

protected:
	APlayerCharacter* PlayerCharacter;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsStackable;
};
