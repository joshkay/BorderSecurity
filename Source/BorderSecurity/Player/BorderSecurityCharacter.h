// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Weapons/Weapon.h"
#include "Components/HealthComponent.h"
#include "BorderSecurityCharacter.generated.h"

UCLASS()
class BORDERSECURITY_API ABorderSecurityCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABorderSecurityCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	void SetFireRotation(FRotator Rotation);

	// Start firing weapon
	UFUNCTION()
	virtual void StartFire();

	// Stop firing weapon
	UFUNCTION()
	virtual void StopFire();

	void SelectWeaponIndex(int32 Index);
	void SelectWeapon(AWeapon* NewWeapon);
	AWeapon* GetSelectedWeapon();

	FORCEINLINE bool IsFiring() { return bIsFiring; }

	FORCEINLINE UHealthComponent* GetHealthComponent() { return HealthComponent; }

protected:
	// Health
	virtual void Killed(AController* EventInstigator, AActor* DamageCauser);

	// Weapons
	void UpdateFireWeapon();

	void InitializeWeapons();
	void InitializeWeapon(TSubclassOf<AWeapon> WeaponClass);
	virtual void WeaponInitialized(AWeapon* Weapon);

	void DestroyCharacter();

protected:
	// Components
	UPROPERTY(EditAnywhere, Category = HP)
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, Category = Death)
	float TimeToDestroyAfterDeath;

	bool bEnabled;

	FTimerHandle DestroyTimerHandle;

protected:
	// The weapon to use for this character
	UPROPERTY(EditAnywhere, Category = Weapons, BlueprintReadWrite)
	TArray<TSubclassOf<AWeapon>> WeaponClasses;

	// Direction from mouse to world
	FRotator CurrentRotation;

	// Is character firing
	bool bIsFiring;

	// Current weapon of player
	int32 SelectedWeaponIndex;

	TArray<AWeapon*> Weapons;
};