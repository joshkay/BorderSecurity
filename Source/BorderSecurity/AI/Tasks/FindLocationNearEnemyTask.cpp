// Josh Kay 2015

#include "BorderSecurity.h"
#include "Enemies/Minion/MinionAIController.h"
#include "Enemies/Minion/MinionCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "FindLocationNearEnemyTask.h"

EBTNodeResult::Type UFindLocationNearEnemyTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMinionAIController* MinionController = Cast<AMinionAIController>(OwnerComp.GetAIOwner());
	if (MinionController == NULL)
	{
		return EBTNodeResult::Failed;
	}

	APawn* Minion = MinionController->GetPawn();
	ABorderItem* Enemy = MinionController->GetEnemy();
	if (Enemy && Minion)
	{
		const float SearchRadius = 500.0f;
		const FVector SearchOrigin = Enemy->GetActorLocation() + 3000.0f * (Minion->GetActorLocation() - Enemy->GetActorLocation()).GetSafeNormal();
		const FVector Loc = UNavigationSystem::GetRandomReachablePointInRadius(MinionController, SearchOrigin, SearchRadius);
		if (Loc != FVector::ZeroVector)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID(), Loc);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}