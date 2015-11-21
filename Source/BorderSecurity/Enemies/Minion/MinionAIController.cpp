// Josh Kay 2015

#include "BorderSecurity.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "MinionCharacter.h"
#include "MinionAIController.h"

AMinionAIController::AMinionAIController()
	: Super()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	BehaviorComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComponent"));
}

void AMinionAIController::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);

	AMinionCharacter* Minion = Cast<AMinionCharacter>(InPawn);
	if (Minion && Minion->MinionBehavior)
	{
		BlackboardComponent->InitializeBlackboard(*Minion->MinionBehavior->BlackboardAsset);

		EnemyKeyID = BlackboardComponent->GetKeyID("Enemy");
		DestinationKeyID = BlackboardComponent->GetKeyID("Destination");

		BehaviorComponent->StartTree(*Minion->MinionBehavior);
	}
}

void AMinionAIController::AttackEnemy()
{

}

void AMinionAIController::SetEnemy(ABorderItem* Actor)
{
	if (BlackboardComponent)
	{
		BlackboardComponent->SetValue<UBlackboardKeyType_Object>(EnemyKeyID, Actor);
		SetFocus(Actor);
	}
}

ABorderItem* AMinionAIController::GetEnemy()
{
	if (BlackboardComponent)
	{
		return Cast<ABorderItem>(BlackboardComponent->GetValue<UBlackboardKeyType_Object>(EnemyKeyID));
	}

	return NULL;
}

void AMinionAIController::SearchForEnemy()
{
	APawn* Minion = GetPawn();
	if (Minion == NULL)
	{
		return;
	}

	const FVector MinionLocation = Minion->GetActorLocation();
	float BestDistSq = MAX_FLT;
	ABorderItem* BestItem = NULL;

	for (TActorIterator<ABorderItem> BorderActorItr(GetWorld()); BorderActorItr; ++BorderActorItr)
	{
		ABorderItem* BorderItem = *BorderActorItr;
		if (BorderItem)
		{
			const float DistSq = (BorderItem->GetActorLocation() - MinionLocation).SizeSquared();
			if (DistSq < BestDistSq)
			{
				BestDistSq = DistSq;
				BestItem = BorderItem;
			}
		}
	}

	if (BestItem)
	{
		SetEnemy(BestItem);
	}
}