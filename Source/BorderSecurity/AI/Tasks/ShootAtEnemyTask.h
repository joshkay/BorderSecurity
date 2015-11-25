// Josh Kay 2015

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "ShootAtEnemyTask.generated.h"

/**
 * 
 */
UCLASS()
class BORDERSECURITY_API UShootAtEnemyTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	bool CanAttack(AMinionCharacter* Minion, ABorderItem* Enemy);
	void AttackEnemy(AMinionCharacter* Minion, ABorderItem* Enemy);
};