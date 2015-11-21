// Fill out your copyright notice in the Description page of Project Settings.

#include "BorderSecurity.h"
#include "Player/GuardCharacter.h"
#include "PlayerAnimInstance.h"

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AGuardCharacter* Character = Cast<AGuardCharacter>(TryGetPawnOwner());
	if (Character)
	{
		// Used for turning animation
		TurnSpeed = Character->GetTurnSpeed();
		// Used for firing animation
		bIsFiring = Character->IsFiring();
	}
}