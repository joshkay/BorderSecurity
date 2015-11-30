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
	InitializeWeapon();

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

void ABorderSecurityCharacter::InitializeWeapon()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.Owner = this;

	Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, FVector::ZeroVector, GetControlRotation(), SpawnParams);
	Weapon->AttachRootComponentToActor(this);
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

void ABorderSecurityCharacter::UpdateFireWeapon()
{
	if (bIsFiring)
	{
		// fire the characters weapon if its ready
		if (Weapon && Weapon->CanAttack())
		{
			Weapon->Attack(CurrentRotation);
		}
	}
}