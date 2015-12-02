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
	Attacked();
}

void AWeapon::Attacked()
{
	TimeSinceLastAttack = 0.f;
}