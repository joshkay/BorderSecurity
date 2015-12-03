// Josh Kay 2015

#include "BorderSecurity.h"
#include "ExplosiveProjectile.h"

void AExplosiveProjectile::DestroyProjectile()
{
	Super::DestroyProjectile();

	//TArray<AActor*> IgnoredActors;

	UGameplayStatics::ApplyRadialDamageWithFalloff(this, BaseExplosiveDamage, MinExplosiveDamage,
		GetActorLocation(), ExplosiveInnerRadius, ExplosiveOuterRadius, ExplosiveDamageFalloff,
		UDamageType::StaticClass(), IgnoredActors, this, Instigator->GetController());

	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosiveEffect, GetActorLocation());
}

void AExplosiveProjectile::UpgradeDamage(float Amount)
{
	Super::UpgradeDamage(Amount);

	//MinExplosiveDamage *= Amount;
	BaseExplosiveDamage *= Amount;
}
