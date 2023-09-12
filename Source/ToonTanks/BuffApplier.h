// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuffApplier.generated.h"

class AToonTanksGameMode;
class UBuff;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UBuffApplier : public UActorComponent
{
	GENERATED_BODY()

public:	
	void SetBuffRotation();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBuffApplied);
	FBuffApplied BuffAppliedEvent;

protected:
	virtual void BeginPlay() override;

private:
	void SetupInput();
	void ApplyBuff(const int32 Index);
	bool RotationContainsBuffOfType(TSubclassOf<UBuff> BuffClass);

	UFUNCTION(BlueprintCallable)
	UBuff* GetBuffInRotation(int Index);
	
	UPROPERTY(EditAnywhere, Category = "Buffs", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UBuff>> AvailableBuffs;
	
	UPROPERTY(VisibleInstanceOnly, Category = "Buffs", meta = (AllowPrivateAccess = "true"))
	TSet<FString> CurrentActiveBuffs;

	UPROPERTY(VisibleInstanceOnly, Category = "Buffs", meta = (AllowPrivateAccess = "true"))
	TArray<UBuff*> CurrentBuffRotation;
	
	DECLARE_DELEGATE_OneParam(FBuffChooseDelegate, const int32);

	AToonTanksGameMode* ToonTanksGameMode;
	
	int BuffLimit = 2;
	bool bCanApplyBuffs;
};
