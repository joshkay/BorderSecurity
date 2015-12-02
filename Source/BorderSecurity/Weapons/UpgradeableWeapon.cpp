// Josh Kay 2015

#include "BorderSecurity.h"
#include "Player/BorderSecurityCharacter.h"
#include "Player/BorderSecurityPlayerState.h"
#include "UpgradeableWeapon.h"

void AUpgradeableWeapon::Upgrade(FUpgradeInfo UpgradeInfo)
{
	//int32 UpgradeIndex = AvailableUpgrades.Find(UpgradeInfo);
	//if (AvailableUpgrades.IsValidIndex(UpgradeIndex))
	{
		//AvailableUpgrades.RemoveAt(UpgradeIndex);

		//UpgradeInfo->bUsed = true;
		ChargePlayer(UpgradeInfo.Cost);
		ApplyUpgrade(UpgradeInfo.Type, UpgradeInfo.Amount);
	}
}

void AUpgradeableWeapon::ChargePlayer(int32 Cost)
{
	ABorderSecurityCharacter* Character = Cast<ABorderSecurityCharacter>(GetOwner());
	if (Character)
	{
		ABorderSecurityPlayerState* PlayerState = Cast<ABorderSecurityPlayerState>(Character->PlayerState);
		if (PlayerState)
		{
			PlayerState->Money -= Cost;
		}
	}
}

TArray<FUpgradeInfo> AUpgradeableWeapon::GetAvailableUpgrades()
{
	AvailableUpgrades.Sort([](const FUpgradeInfo& Upgrade1, const FUpgradeInfo& Upgrade2) {
		return Upgrade1.Cost < Upgrade2.Cost;
	});

	TArray<EUpgradeType> TypesAdded;
	TArray<FUpgradeInfo> LowestUpgrades;
	for (FUpgradeInfo Upgrade : AvailableUpgrades)
	{
		if (Upgrade.bUsed || TypesAdded.Contains(Upgrade.Type))
		{
			continue;
		}

		TypesAdded.Add(Upgrade.Type);
		LowestUpgrades.Add(Upgrade);
	}

	return LowestUpgrades;
}

void AUpgradeableWeapon::ApplyUpgrade(EUpgradeType Type, float Amount)
{
	switch (Type)
	{
	case EUpgradeType::UT_AttackSpeed:
		UpgradeAttackSpeed(Amount);
		return;
	}
}

void AUpgradeableWeapon::UpgradeAttackSpeed(float Amount)
{
	AttackSpeed *= Amount;
}