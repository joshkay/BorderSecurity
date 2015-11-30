// Josh Kay 2015

#pragma once

#include "Weapons/Weapon.h"
#include "UpgradeableWeapon.generated.h"

UENUM(BlueprintType)
enum class EUpgradeType : uint8
{
	UT_Damage			UMETA(DisplayName = "Damage"),
	UT_AttackSpeed		UMETA(DisplayName = "Attack Speed")
};

USTRUCT()
struct FUpgradeInfo
{
	GENERATED_BODY()

	UPROPERTY()
	EUpgradeType Type;

	UPROPERTY()
	float Amount;

	UPROPERTY()
	int32 Cost;
};

UCLASS()
class BORDERSECURITY_API AUpgradeableWeapon : public AWeapon
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = Upgrades)
	TArray<FUpgradeInfo> AvailableUpgrades;
	
	
};
