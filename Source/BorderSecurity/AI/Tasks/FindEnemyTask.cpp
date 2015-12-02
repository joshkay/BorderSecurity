// Josh Kay 2015

#include "BorderSecurity.h"
#include "Enemies/Minion/MinionAIController.h"
#include "Enemies/Minion/MinionCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "FindEnemyTask.h"

EBTNodeResult::Type UFindEnemyTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (GetWorld() == NULL)
	{
		return EBTNodeResult::Failed;
	}

	ABorderItem* Item = GetBorderTarget();
	if (Item)
	{
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID(), Item);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

ABorderItem* UFindEnemyTask::GetBorderTarget()
{
	ABorderItem* Item = GetRandomWall();
	if (!Item)
	{
		Item = GetRandomTower();
	}

	return Item;
}

ABorderWall* UFindEnemyTask::GetRandomWall()
{
	TArray<ABorderWall*> BorderItems;
	for (TActorIterator<ABorderWall> BorderActorItr(GetWorld()); BorderActorItr; ++BorderActorItr)
	{
		ABorderWall* BorderItem = *BorderActorItr;
		if (BorderItem)
		{
			BorderItems.Add(BorderItem);
		}
	}

	if (BorderItems.Num() > 0)
	{
		ABorderWall* Item = BorderItems[FMath::RandRange(0, BorderItems.Num() - 1)];
		if (Item)
		{
			return Item;
		}
	}

	return nullptr;
}

ABorderTower* UFindEnemyTask::GetRandomTower()
{
	TArray<ABorderTower*> BorderItems;
	for (TActorIterator<ABorderTower> BorderActorItr(GetWorld()); BorderActorItr; ++BorderActorItr)
	{
		ABorderTower* BorderItem = *BorderActorItr;
		if (BorderItem)
		{
			BorderItems.Add(BorderItem);
		}
	}

	if (BorderItems.Num() > 0)
	{
		ABorderTower* Item = BorderItems[FMath::RandRange(0, BorderItems.Num() - 1)];
		if (Item)
		{
			return Item;
		}
	}

	return nullptr;
}