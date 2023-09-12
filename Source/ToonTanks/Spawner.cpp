// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "BaseCharacter.h"

ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawner::SpawnCurrentEnemyWave(TArray<TSubclassOf<ABaseCharacter>>& RoundWave)
{
	for (auto Enemy : RoundWave)
	{
		const int SpawnPointIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
		const auto SpawnPoint = SpawnPoints[SpawnPointIndex];
	
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(Enemy, SpawnPoint->GetActorLocation(), SpawnPoint->GetActorRotation());
		
		CurrentSpawnedEnemies.Add(SpawnedActor);
	}
}

bool ASpawner::CanSpawn() const
{
	if (!CurrentSpawnedEnemies.IsEmpty())
	{
		return false;
	}

	return true;
}

