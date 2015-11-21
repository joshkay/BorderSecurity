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

	bool CanFire();

	void Fire();
	void Fire(FRotator Direction);

protected:

	void Fired();

	UPROPERTY(EditAnywhere, Category = Firing)
	float RateOfFire;

	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<AProjectile> ProjectileClass;

	// Time since the last projectile was shot
	float TimeSinceLastFire;
};