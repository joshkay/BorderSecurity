// Josh Kay 2015

#include "BorderSecurity.h"
#include "Enemies/Minion/MinionAIController.h"
#include "Enemies/Minion/MinionCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "ShootAtEnemyTask.h"

EBTNodeResult::Type UShootAtEnemyTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMinionAIController* MinionController = Cast<AMinionAIController>(OwnerComp.GetAIOwner());
	if (MinionController == NULL)
	{
		return EBTNodeResult::Failed;
	}

	AMinionCharacter* Minion = Cast<AMinionCharacter>(MinionController->GetPawn());
	ABorderItem* Enemy = MinionController->GetEnemy();
	if (Enemy && Minion)
	{
		FVector Origin;
		FVector BoxEtent;
		Enemy->GetActorBounds(false, Origin, BoxEtent);

		FVector WallTarget = Enemy->GetActorLocation() + FVector(-BoxEtent.X / 2, 0.f, BoxEtent.Z);
		FRotator Rotator = (WallTarget - Minion->GetActorLocation()).Rotation();
		//Rotator.Pitch += 150.f;

		Minion->SetFireRotation(Rotator);
		Minion->StartFire();

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}