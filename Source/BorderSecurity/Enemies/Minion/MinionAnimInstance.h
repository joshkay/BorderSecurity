// Josh Kay 2015

#pragma once

#include "Animation/AnimInstance.h"
#include "MinionAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BORDERSECURITY_API UMinionAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bFiring;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float RateOfFire;
};