// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

struct FRoundWave;
class ABaseCharacter;

UCLASS()
class TOONTANKS_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawner();

	void SpawnCurrentEnemyWave(TArray<TSubclassOf<ABaseCharacter>>& RoundWave);
	bool CanSpawn() const;

	UPROPERTY(VisibleInstanceOnly)
	TArray<AActor*> CurrentSpawnedEnemies;

private:
	UPROPERTY(EditAnywhere)
	TArray<AActor*> SpawnPoints;
};
