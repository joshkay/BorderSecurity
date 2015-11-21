// Josh Kay 2015

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FindEnemyTask.generated.h"

/**
 * 
 */
UCLASS()
class BORDERSECURITY_API UFindEnemyTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};