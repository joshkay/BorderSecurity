// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Weapons/Weapon.h"
#include "BorderSecurityCharacter.generated.h"

UCLASS()
class BORDERSECURITY_API ABorderSecurityCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABorderSecurityCharacter();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	void SetFireRotation(FRotator Rotation);

	// Start firing weapon
	UFUNCTION()
	virtual void StartFire();

	// Stop firing weapon
	UFUNCTION()
	virtual void StopFire();

	FORCEINLINE bool IsFiring() { return bIsFiring; }

protected:
	// Deal with firing the weapon
	void UpdateFireWeapon();

	void InitializeWeapon();

	// Direction from mouse to world
	FRotator CurrentRotation;

	// Is character firing
	bool bIsFiring;

	// Current weapon of player
	AWeapon* Weapon;

	// The weapon to use for this character
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeapon> WeaponClass;
};