// Josh Kay 2015

#pragma once

#include "Blueprint/UserWidget.h"
#include "Weapons/UpgradeableWeapon.h"
#include "WeaponUpgradeWidget.h"
#include "WeaponWidget.generated.h"

/**
 * 
 */
UCLASS()
class BORDERSECURITY_API UWeaponWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;
	void NativeDestruct() override;

	FORCEINLINE void SetWeapon(AWeapon* NewWeapon) { Weapon = NewWeapon; }
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Weapon)
	UButton* GetWeaponButton();

	UFUNCTION(BlueprintImplementableEvent, Category = Weapon)
	UPanelWidget* GetUpgradeBox();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	FText GetWeaponName() const;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	FSlateColor GetButtonBrush() const;

	void LoadUpgrades();
	
	UFUNCTION()
	void OnWeaponClicked();

	UPROPERTY(EditDefaultsOnly, Category = Upgrades)
	TSubclassOf<UWeaponUpgradeWidget> WeaponUpgradeClass;

	AWeapon* Weapon;
};
