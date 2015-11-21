// Josh Kay 2015

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FindLocationNearEnemyTask.generated.h"

/**
 * 
 */
UCLASS()
class BORDERSECURITY_API UFindLocationNearEnemyTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
