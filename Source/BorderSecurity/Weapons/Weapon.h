// Josh Kay 2015

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.h"
#include "Weapon.generated.h"

UCLASS()
class BORDERSECURITY_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual bool CanAttack();

	virtual void Attack();

	FORCEINLINE void SetAttackDirection(FRotator Direction) { AttackDirection = Direction; }
	FORCEINLINE float GetAttackSpeed() { return AttackSpeed; }
	FORCEINLINE FText GetDisplayName() { return DisplayName; }

protected:
	void Attacked();

	UPROPERTY(EditDefaultsOnly, Category = Display)
	FText DisplayName;

	UPROPERTY(EditAnywhere, Category = Attack)
	float AttackSpeed;

	FRotator AttackDirection;

	// Time since the last projectile was shot
	float TimeSinceLastAttack;
};