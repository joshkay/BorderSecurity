// Josh Kay 2015

#include "BorderSecurity.h"
#include "WeaponHolderWidget.h"

void UWeaponHolderWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWeaponHolderWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UWeaponHolderWidget::AddWeapon(AWeapon* Weapon)
{
	UWeaponWidget* WeaponWidget = CreateWidget<UWeaponWidget>(GetOwningPlayer(), WeaponClass);
	WeaponWidget->SetWeapon(Weapon);

	UPanelSlot* PanelSlot = Cast<UPanelSlot>(GetWeaponBox()->AddChild(WeaponWidget));
}