#include "ArtilleryBuff.h"
#include "PlayerCharacter.h"

void UArtilleryBuff::ApplyBuff()
{
	Super::ApplyBuff();

	if (PlayerCharacter == nullptr)
	{
		return;
	}

	PlayerCharacter->ProjectilesPerShot += AdditionalProjectileCount;
}

void UArtilleryBuff::RemoveBuff()
{
	Super::RemoveBuff();
	
	if (PlayerCharacter == nullptr)
	{
		return;
	}

	PlayerCharacter->ProjectilesPerShot -= AdditionalProjectileCount;
}
