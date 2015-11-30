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
	virtual void Attack(FRotator Direction);

	FORCEINLINE float GetAttackSpeed() { return AttackSpeed; }

protected:
	void Attacked();

	UPROPERTY(EditAnywhere, Category = Attack)
	float AttackSpeed;

	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<AProjectile> ProjectileClass;

	// Time since the last projectile was shot
	float TimeSinceLastAttack;
};