// Fill out your copyright notice in the Description page of Project Settings.

#include "BorderSecurity.h"
#include "BorderSecurityPlayerController.h"
#include "BorderSecurityCharacter.h"

// Sets default values
ABorderSecurityCharacter::ABorderSecurityCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentRotation = FRotator::ZeroRotator;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void ABorderSecurityCharacter::BeginPlay()
{
	Super::BeginPlay();

	bEnabled = true;
	InitializeWeapons();

	GEngine->GameViewport->SetCaptureMouseOnClick(EMouseCaptureMode::CapturePermanently);
	GEngine->GameViewport->Viewport->LockMouseToViewport(true);
	GEngine->GameViewport->Viewport->CaptureMouse(true);
}

void ABorderSecurityCharacter::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);

	if (!bEnabled)
	{
		return;
	}
	
	UpdateFireWeapon();
}

float ABorderSecurityCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!bEnabled)
	{
		return Damage;
	}

	float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	// Apply damage and destroy if not alive
	HealthComponent->TakeDamage(ActualDamage);
	if (!HealthComponent->IsAlive())
	{
		Killed(EventInstigator, DamageCauser);
	}

	return ActualDamage;
}

void ABorderSecurityCharacter::Killed(AController* EventInstigator, AActor* DamageCauser)
{
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorTickEnabled(false);

	bEnabled = false;

	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &ABorderSecurityCharacter::DestroyCharacter, TimeToDestroyAfterDeath, false);
}

void ABorderSecurityCharacter::SetFireRotation(FRotator Rotation)
{
	if (!bEnabled)
	{
		return;
	}

	CurrentRotation = Rotation;
}


void ABorderSecurityCharacter::InitializeWeapons()
{
	SelectedWeaponIndex = 0;
	for (TSubclassOf<AWeapon> WeaponClass : WeaponClasses)
	{
		InitializeWeapon(WeaponClass);
	}
}

void ABorderSecurityCharacter::InitializeWeapon(TSubclassOf<AWeapon> WeaponClass)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.Owner = this;

	AWeapon* Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, FVector::ZeroVector, GetControlRotation(), SpawnParams);
	Weapon->AttachRootComponentToActor(this);

	Weapons.Add(Weapon);

	WeaponInitialized(Weapon);
}

void ABorderSecurityCharacter::WeaponInitialized(AWeapon* Weapon)
{

}

void ABorderSecurityCharacter::SelectWeaponIndex(int32 Index)
{
	if (Weapons.IsValidIndex(Index))
	{
		SelectedWeaponIndex = Index;
	}
}

void ABorderSecurityCharacter::SelectWeapon(AWeapon* NewWeapon)
{
	int32 Index = Weapons.Find(NewWeapon);
	if (Weapons.IsValidIndex(Index))
	{
		SelectedWeaponIndex = Index;
	}
}

void ABorderSecurityCharacter::DestroyCharacter()
{
	Destroy();
}

void ABorderSecurityCharacter::StartFire()
{
	if (!bEnabled)
	{
		return;
	}

	bIsFiring = true;
}

void ABorderSecurityCharacter::StopFire()
{
	if (!bEnabled)
	{
		return;
	}

	bIsFiring = false;
}

AWeapon* ABorderSecurityCharacter::GetSelectedWeapon()
{
	if (Weapons.IsValidIndex(SelectedWeaponIndex))
	{
		return Weapons[SelectedWeaponIndex];
	}
	return nullptr;
}

void ABorderSecurityCharacter::UpdateFireWeapon()
{
	if (bIsFiring)
	{
		AWeapon* Weapon = GetSelectedWeapon();
		// fire the characters weapon if its ready
		if (Weapon && Weapon->CanAttack())
		{
			Weapon->SetAttackDirection(CurrentRotation);
			Weapon->Attack();
		}
	}
}