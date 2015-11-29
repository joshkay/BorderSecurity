// Josh Kay 2015

#pragma once

#include "Player/BorderSecurityCharacter.h"
#include "BorderSecurityEnemy.generated.h"

/**
 * 
 */
UCLASS()
class BORDERSECURITY_API ABorderSecurityEnemy : public ABorderSecurityCharacter
{
	GENERATED_BODY()

public:
	void BeginPlay() override;

protected:
	void Killed(AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Worth)
	int32 MoneyValue;
	
};
