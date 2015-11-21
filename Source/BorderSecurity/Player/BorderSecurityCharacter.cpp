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
}

// Called when the game starts or when spawned
void ABorderSecurityCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitializeWeapon();
}

void ABorderSecurityCharacter::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);

	/*if (!GEngine->GameViewport->Viewport->HasMouseCapture())
	{
		GEngine->GameViewport->SetCaptureMouseOnClick(EMouseCaptureMode::CapturePermanently);
		GEngine->GameViewport->Viewport->LockMouseToViewport(true);
		GEngine->GameViewport->Viewport->CaptureMouse(true);
	}*/

	UpdateFireWeapon();
}

void ABorderSecurityCharacter::SetFireRotation(FRotator Rotation)
{
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

void ABorderSecurityCharacter::StartFire()
{
	bIsFiring = true;
}

void ABorderSecurityCharacter::StopFire()
{
	bIsFiring = false;
}

void ABorderSecurityCharacter::UpdateFireWeapon()
{
	if (bIsFiring)
	{
		// fire the characters weapon if its ready
		if (Weapon && Weapon->CanFire())
		{
			Weapon->Fire(CurrentRotation);
		}
	}
}