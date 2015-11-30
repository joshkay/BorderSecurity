// Josh Kay 2015

#include "BorderSecurity.h"
#include "Weapon.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	TimeSinceLastAttack = 0.f;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	TimeSinceLastAttack += DeltaTime;
}

bool AWeapon::CanAttack()
{
	return TimeSinceLastAttack >= AttackSpeed;
}

void AWeapon::Attack()
{
	// Spawn a projectile when weapon fires!
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Instigator;
	SpawnParams.Owner = this;

	GetWorld()->SpawnActor<AProjectile>(ProjectileClass, GetActorLocation(), GetActorRotation(), SpawnParams);

	Attacked();
}

void AWeapon::Attack(FRotator Direction)
{
	// Spawn a projectile when weapon fires!
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Instigator;
	SpawnParams.Owner = this;

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, GetActorLocation(), Direction, SpawnParams);

	Attacked();
}

void AWeapon::Attacked()
{
	TimeSinceLastAttack = 0.f;
}