// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStatus.h"
#include "PlayerCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

enum class GameStatus : uint8;
class ABaseCharacter;
class AToonTanksPlayerController;
class ASpawner;
class UBuffApplier;

USTRUCT()
struct FRoundWave
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ABaseCharacter>> Enemies;
};

USTRUCT()
struct FGameRound
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TArray<FRoundWave> Wave;
};

UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AToonTanksGameMode();

	void ActorDied(AActor* DeadActor);
	bool IsBreakTime() const { return GameStatus == GameStatus::BreakTime; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void HandleGameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void ShowStartMenu();

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

	UFUNCTION(BlueprintImplementableEvent)
	void BreakTime(bool bActive);

	UFUNCTION(BlueprintCallable)
	float GetTime();

private:
	void PrepareGame();
	void StartGameBeginTimer();
	void SetupRounds();
	void BeginBreakTime();

	UFUNCTION()
	void StartNewRound();
	void FinishGame();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	GameStatus GameStatus = GameStatus::StartMenu;

	UPROPERTY(EditAnywhere)
	TArray<FGameRound> GameRounds;

	UPROPERTY(EditAnywhere)
	int32 RoundWaitTime = 5;

	APlayerCharacter* Tank;
	AToonTanksPlayerController* ToonTanksPlayerController;
	ASpawner* EnemySpawner;
	UBuffApplier* BuffApplier;
	
	int32 RoundIndex = 0;
	int32 WaveIndex = 0;

	float StartDelay = 3.f;
	bool bBreakTime = true;
	
	FTimerHandle RoundTimerHandle;
};
