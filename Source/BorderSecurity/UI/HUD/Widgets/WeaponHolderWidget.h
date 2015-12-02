// Josh Kay 2015

#pragma once

#include "Blueprint/UserWidget.h"
#include "WeaponWidget.h"
#include "WeaponHolderWidget.generated.h"

UCLASS()
class BORDERSECURITY_API UWeaponHolderWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;
	void NativeDestruct() override;

	void AddWeapon(AWeapon* Weapon);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Weapon)
	UPanelWidget* GetWeaponBox();

	UPROPERTY(EditDefaultsOnly, Category = Upgrades)
	TSubclassOf<UWeaponWidget> WeaponClass;
};
