#include "BTService_IsInRange.h"
#include "AIController.h"
#include "BaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_IsInRange::UBTService_IsInRange()
{
	NodeName = TEXT("Is In Range");
}

void UBTService_IsInRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr || PlayerPawn->IsHidden())
    {
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), false);
		return;
    }

    const ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if (BaseCharacter == nullptr)
    {
    	return;
    }

	const float Distance = FVector::Dist(PlayerPawn->GetActorLocation(), BaseCharacter->GetActorLocation());

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), Distance <= MaximumDistance);
}
