// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "BaseCharacter.h"
#include "BuffApplier.h"
#include "GameStatus.h"
#include "PlayerCharacter.h"
#include "Spawner.h"
#include "ToonTanksPlayerController.h"

AToonTanksGameMode::AToonTanksGameMode()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();
        
        GameOver(false);
    }
    else if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(DeadActor))
    {
        BaseCharacter->HandleDestruction();
    }

    if (EnemySpawner)
    {
        const int32 Index = EnemySpawner->CurrentSpawnedEnemies.IndexOfByKey(DeadActor);
    
        if (Index != INDEX_NONE)
        {
            EnemySpawner->CurrentSpawnedEnemies.RemoveAt(Index);
        }
    }
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    ShowStartMenu();
}

void AToonTanksGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    SetupRounds();
}

float AToonTanksGameMode::GetTime()
{
    return GetWorldTimerManager().GetTimerRemaining(RoundTimerHandle);
}

void AToonTanksGameMode::PrepareGame()
{
    GameStatus = GameStatus::Started;
    
    if (ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(true);
    }

    if (Tank)
    {
        Tank->SetEnabledState(true);
    }
}

void AToonTanksGameMode::HandleGameStart()
{
    Tank = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    EnemySpawner = Cast<ASpawner>(UGameplayStatics::GetActorOfClass(this, ASpawner::StaticClass()));
    BuffApplier = Tank->FindComponentByClass<UBuffApplier>();

    StartGame();

    if (ToonTanksPlayerController)
    {
        StartGameBeginTimer();
    }

    if (BuffApplier)
    {
        BuffApplier->BuffAppliedEvent.AddDynamic(this, &AToonTanksGameMode::StartNewRound);
    }
}

void AToonTanksGameMode::StartGameBeginTimer()
{
    ToonTanksPlayerController->SetPlayerEnabledState(false);

    FTimerHandle PlayerEnableTimerHandle;
    const FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(this, &AToonTanksGameMode::PrepareGame);

    GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
}

void AToonTanksGameMode::SetupRounds()
{
    if (GameStatus == GameStatus::BreakTime || GameStatus == GameStatus::StartMenu || GameStatus == GameStatus::Readying)
    {
        return;
    }
	
    FGameRound CurrentGameRound = GameRounds[RoundIndex];
    TArray<FRoundWave> CurrentWave = CurrentGameRound.Wave;

    if (!EnemySpawner->CanSpawn())
    {
        return;
    }

    if (WaveIndex >= CurrentWave.Num())
    {
        BeginBreakTime();
        return;
    }

    EnemySpawner->SpawnCurrentEnemyWave(CurrentWave[WaveIndex].Enemies);

    WaveIndex++;
}

void AToonTanksGameMode::BeginBreakTime()
{
    if (RoundIndex == GameRounds.Num() - 1)
    {
        FinishGame();
        return;
    }
    
    WaveIndex = 0;
    GameStatus = GameStatus::BreakTime;
    
    BreakTime(true);
    GetWorldTimerManager().SetTimer(RoundTimerHandle, this, &AToonTanksGameMode::StartNewRound, RoundWaitTime, false);
}

void AToonTanksGameMode::StartNewRound()
{
    if (GameStatus != GameStatus::BreakTime)
    {
        return;
    }
    
    if (BuffApplier)
    {
        BuffApplier->SetBuffRotation();
    }

	RoundIndex++;
    BreakTime(false);
    GameStatus = GameStatus::Started;
}

void AToonTanksGameMode::FinishGame()
{
    GameOver(true);
    GameStatus = GameStatus::Ending;
}
