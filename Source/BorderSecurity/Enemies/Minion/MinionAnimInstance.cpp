// Josh Kay 2015

#include "BorderSecurity.h"
#include "Player/BorderSecurityCharacter.h"
#include "MinionAnimInstance.h"

void UMinionAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ABorderSecurityCharacter* Character = Cast<ABorderSecurityCharacter>(TryGetPawnOwner());
	if (Character)
	{
		Speed = Character->GetVelocity().Size();
		bFiring = Character->IsFiring();

		AWeapon* Weapon = Character->GetSelectedWeapon();
		if (Weapon)
		{
			RateOfFire = Weapon->GetAttackSpeed();
		}
	}
}