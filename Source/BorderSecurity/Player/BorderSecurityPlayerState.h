// Josh Kay 2015

#pragma once

#include "GameFramework/PlayerState.h"
#include "BorderSecurityPlayerState.generated.h"

UCLASS(Config=Game)
class BORDERSECURITY_API ABorderSecurityPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(config)
	int32 Money;
	
};