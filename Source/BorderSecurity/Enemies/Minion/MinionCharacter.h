// Josh Kay 2015

#pragma once

#include "GameFramework/Character.h"
#include "Enemies/BorderSecurityEnemy.h"
#include "MinionCharacter.generated.h"

UCLASS()
class BORDERSECURITY_API AMinionCharacter : public ABorderSecurityEnemy
{
	GENERATED_BODY()

public:
	AMinionCharacter();

	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* MinionBehavior;
};