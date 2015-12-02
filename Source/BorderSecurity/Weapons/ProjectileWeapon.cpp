// Josh Kay 2015

#include "BorderSecurity.h"
#include "ProjectileWeapon.h"

void AProjectileWeapon::BeginPlay()
{
	Super::BeginPlay();

	DamageUpgrade = 1.f;
	SpeedUpgrade = 1.f;
}

void AProjectileWeapon::Attack()
{
	Super::Attack();

	// Spawn a projectile when weapon fires!
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Instigator;
	SpawnParams.Owner = this;

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, GetActorLocation(), AttackDirection, SpawnParams);
	Projectile->UpgradeDamage(DamageUpgrade);
	Projectile->UpgradeSpeed(SpeedUpgrade);
}

void AProjectileWeapon::ApplyUpgrade(EUpgradeType Type, float Amount)
{
	Super::ApplyUpgrade(Type, Amount);

	switch (Type)
	{
	case EUpgradeType::UT_Damage:
		UpgradeDamage(Amount);
		return;
	case EUpgradeType::UT_Speed:
		UpgradeSpeed(Amount);
		return;
	}
}

void AProjectileWeapon::UpgradeDamage(float Amount)
{
	DamageUpgrade *= Amount;
}

void AProjectileWeapon::UpgradeSpeed(float Amount)
{
	SpeedUpgrade *= Amount;
}
