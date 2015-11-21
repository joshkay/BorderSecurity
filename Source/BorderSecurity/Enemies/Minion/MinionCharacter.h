// Josh Kay 2015

#pragma once

#include "GameFramework/Character.h"
#include "Player/BorderSecurityCharacter.h"
#include "MinionCharacter.generated.h"

UCLASS()
class BORDERSECURITY_API AMinionCharacter : public ABorderSecurityCharacter
{
	GENERATED_BODY()

public:
	AMinionCharacter();

	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* MinionBehavior;
};