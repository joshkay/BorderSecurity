// Josh Kay 2015

#pragma once

#include "Weapons/UpgradeableWeapon.h"
#include "ProjectileWeapon.generated.h"

UCLASS()
class BORDERSECURITY_API AProjectileWeapon : public AUpgradeableWeapon
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void Attack() override;

protected:	
	virtual void ApplyUpgrade(EUpgradeType Type, float Amount) override;

	void UpgradeDamage(float Amount);
	void UpgradeSpeed(float Amount);

	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<AProjectile> ProjectileClass;

	float DamageUpgrade;
	float SpeedUpgrade;
};
