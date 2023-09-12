// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buff.h"
#include "HatBuff.generated.h"

UCLASS()
class TOONTANKS_API UHatBuff : public UBuff
{
	GENERATED_BODY()
	
	virtual void ApplyBuff() override;
	virtual void RemoveBuff() override;

	UPROPERTY(EditAnywhere,  meta = (AllowPrivateAccess = "true"))
	UStaticMesh* Hat;
};
