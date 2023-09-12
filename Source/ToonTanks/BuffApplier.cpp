#include "BuffApplier.h"
#include "Buff.h"
#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"

void UBuffApplier::BeginPlay()
{
	Super::BeginPlay();

	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	
	SetBuffRotation();
	SetupInput();
}

void UBuffApplier::ApplyBuff(const int32 Index)
{
	if (ToonTanksGameMode && !ToonTanksGameMode->IsBreakTime())
	{
		return;
	}
	
	UBuff* ChosenBuff = GetBuffInRotation(Index);
	if (ChosenBuff)
	{
		ChosenBuff->ApplyBuff();
		CurrentActiveBuffs.Add(ChosenBuff->GetBuffName());
	}

	CurrentBuffRotation.Empty();
	BuffAppliedEvent.Broadcast();
}

UBuff* UBuffApplier::GetBuffInRotation(int Index)
{
	return CurrentBuffRotation[Index];
}

void UBuffApplier::SetBuffRotation()
{
	if (AvailableBuffs.Num() == 0)
	{
		return;
	}

	while (CurrentBuffRotation.Num() < BuffLimit)
	{
		UClass* BuffClass = AvailableBuffs[FMath::RandRange(0, AvailableBuffs.Num() - 1)].Get();
		if (BuffClass == nullptr)
		{
			continue;
		}

		UBuff* Buff = NewObject<UBuff>(this, BuffClass);
		if (!Buff || RotationContainsBuffOfType(BuffClass))
		{
			continue;
		}

		if (!Buff->IsStackable() && CurrentActiveBuffs.Contains(Buff->GetBuffName()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Found a non stackable buff.. refreshing - %s"), *Buff->GetName());
			continue;
		}
	
		CurrentBuffRotation.AddUnique(Buff);
	}
}

bool UBuffApplier::RotationContainsBuffOfType(TSubclassOf<UBuff> BuffClass)
{
	for (const UBuff* Buff : CurrentBuffRotation)
	{
		if (Buff && Buff->IsA(BuffClass))
		{
			return true;
		}
	}
	return false;
}

void UBuffApplier::SetupInput()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController)
	{
		return;
	}
	
	PlayerController
		->InputComponent
		->BindAction<FBuffChooseDelegate>(TEXT("SelectBuff1"), IE_Pressed, this, &UBuffApplier::ApplyBuff, 0);

	PlayerController
		->InputComponent
		->BindAction<FBuffChooseDelegate>(TEXT("SelectBuff2"), IE_Pressed, this, &UBuffApplier::ApplyBuff, 1);
}

