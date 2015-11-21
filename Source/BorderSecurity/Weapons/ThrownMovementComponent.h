// Josh Kay 2015

#pragma once

#include "GameFramework/ProjectileMovementComponent.h"
#include "ThrownMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class BORDERSECURITY_API UThrownMovementComponent : public UProjectileMovementComponent
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
protected:
	void UpdateRotation();

	UPROPERTY(EditAnywhere, Category = Rotation)
	float RotationSpeed;

	FRotator CurrentRotation;
};
