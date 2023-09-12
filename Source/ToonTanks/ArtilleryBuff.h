#pragma once

#include "CoreMinimal.h"
#include "Buff.h"
#include "ArtilleryBuff.generated.h"

UCLASS()
class TOONTANKS_API UArtilleryBuff : public UBuff
{
	GENERATED_BODY()
	
	virtual void ApplyBuff() override;
	virtual void RemoveBuff() override;

	UPROPERTY(EditAnywhere)
	float AdditionalProjectileCount;
};
