// Josh Kay 2015

#pragma once

#include "Blueprint/UserWidget.h"
#include "Weapons/UpgradeableWeapon.h"
#include "WeaponUpgradeWidget.generated.h"

/**
 * 
 */
UCLASS()
class BORDERSECURITY_API UWeaponUpgradeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;
	void NativeDestruct() override;

	FORCEINLINE void SetUpgrade(FUpgradeInfo NewUpgrade) { WeaponUpgrade = NewUpgrade; }
	FORCEINLINE void SetWeapon(AUpgradeableWeapon* NewWeapon) { Weapon = NewWeapon; }

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = WeaponUpgrade)
	UButton* GetUpgradeButton();

	UFUNCTION(BlueprintCallable, Category = WeaponUpgrade)
	FText GetUpgradeText() const;

	UFUNCTION(BlueprintCallable, Category = WeaponUpgrade)
	ESlateVisibility GetVisibility() const;

	UFUNCTION()
	void OnUpgradeClicked();

	FUpgradeInfo WeaponUpgrade;
	AUpgradeableWeapon* Weapon;
};
