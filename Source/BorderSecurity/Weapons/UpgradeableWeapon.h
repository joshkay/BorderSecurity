// Josh Kay 2015

#pragma once

#include "Weapons/Weapon.h"
#include "UpgradeableWeapon.generated.h"

UENUM(BlueprintType)
enum class EUpgradeType : uint8
{
	UT_AttackSpeed		UMETA(DisplayName = "Attack Speed"),
	UT_Damage			UMETA(DisplayName = "Damage"),
	UT_Speed			UMETA(DisplayName = "Speed")
};

USTRUCT()
struct FUpgradeInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FText DisplayName;

	UPROPERTY(EditAnywhere)
	EUpgradeType Type;

	UPROPERTY(EditAnywhere)
	float Amount;

	UPROPERTY(EditAnywhere)
	int32 Cost;

	UPROPERTY(EditAnywhere, Transient)
	int32 bUsed;
};

UCLASS()
class BORDERSECURITY_API AUpgradeableWeapon : public AWeapon
{
	GENERATED_BODY()
	
public:
	void Upgrade(FUpgradeInfo UpgradeInfo);

	TArray<FUpgradeInfo> GetAvailableUpgrades();

protected:
	virtual void ApplyUpgrade(EUpgradeType Type, float Amount);
	void ChargePlayer(int32 Cost);
	void UpgradeAttackSpeed(float Amount);

	UPROPERTY(EditAnywhere, Category = Upgrades)
	TArray<FUpgradeInfo> AvailableUpgrades;
};
