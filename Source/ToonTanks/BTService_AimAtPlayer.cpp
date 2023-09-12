#include "BTService_AimAtPlayer.h"
#include "AIController.h"
#include "BaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UBTService_AimAtPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr)
	{
		return;
	}

	const ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (BaseCharacter == nullptr)
	{
		return;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), PlayerPawn->GetActorLocation());
	BaseCharacter->RotateTurret(PlayerPawn->GetActorLocation());
}
