// Josh Kay 2015

#pragma once

#include "Weapons/Projectile.h"
#include "ExplosiveProjectile.generated.h"

/**
 * 
 */
UCLASS()
class BORDERSECURITY_API AExplosiveProjectile : public AProjectile
{
	GENERATED_BODY()
	
protected:
	virtual void DestroyProjectile() override;

	virtual void UpgradeDamage(float Amount) override;
	
	UPROPERTY(EditDefaultsOnly, Category = Explosive)
	UParticleSystem* ExplosiveEffect;

	UPROPERTY(EditDefaultsOnly, Category = Explosive)
	float BaseExplosiveDamage;

	UPROPERTY(EditDefaultsOnly, Category = Explosive)
	float MinExplosiveDamage;

	UPROPERTY(EditDefaultsOnly, Category = Explosive)
	float ExplosiveInnerRadius;

	UPROPERTY(EditDefaultsOnly, Category = Explosive)
	float ExplosiveOuterRadius;

	UPROPERTY(EditDefaultsOnly, Category = Explosive)
	float ExplosiveDamageFalloff;
};
