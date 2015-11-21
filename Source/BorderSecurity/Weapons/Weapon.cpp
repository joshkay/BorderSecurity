// Josh Kay 2015

#include "BorderSecurity.h"
#include "Weapon.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	TimeSinceLastFire = 0.f;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	TimeSinceLastFire += DeltaTime;
}

bool AWeapon::CanFire()
{
	return TimeSinceLastFire >= RateOfFire;
}

void AWeapon::Fire()
{
	// Spawn a projectile when weapon fires!
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Instigator;
	SpawnParams.Owner = this;

	GetWorld()->SpawnActor<AProjectile>(ProjectileClass, GetActorLocation(), GetActorRotation(), SpawnParams);

	Fired();
}

void AWeapon::Fire(FRotator Direction)
{
	// Spawn a projectile when weapon fires!
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Instigator;
	SpawnParams.Owner = this;

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, GetActorLocation(), Direction, SpawnParams);

	Fired();
}

void AWeapon::Fired()
{
	TimeSinceLastFire = 0.f;
}