// Josh Kay 2015

#pragma once

#include "AIController.h"
#include "Environment/BorderItem.h"
#include "MinionAIController.generated.h"

/**
 * 
 */
UCLASS()
class BORDERSECURITY_API AMinionAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMinionAIController();

	virtual void Possess(class APawn* InPawn) override;	
	ABorderItem* GetEnemy();
	
protected:
	UPROPERTY()
	UBlackboardComponent* BlackboardComponent;

	UPROPERTY()
	UBehaviorTreeComponent* BehaviorComponent;

	void AttackEnemy();

	void SetEnemy(ABorderItem* InBorderItem);

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SearchForEnemy();

protected:
	uint8 EnemyKeyID;
	uint8 DestinationKeyID;
	
};
