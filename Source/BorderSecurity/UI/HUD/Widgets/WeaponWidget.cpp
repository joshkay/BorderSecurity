// Josh Kay 2015

#include "BorderSecurity.h"
#include "Player/BorderSecurityCharacter.h"
#include "WeaponWidget.h"

void UWeaponWidget::NativeConstruct()
{
	Super::NativeConstruct();

	LoadUpgrades();

	GetWeaponButton()->OnClicked.AddDynamic(this, &UWeaponWidget::OnWeaponClicked);
}

void UWeaponWidget::NativeDestruct()
{
	Super::NativeDestruct();

	GetWeaponButton()->OnClicked.RemoveDynamic(this, &UWeaponWidget::OnWeaponClicked);
}

FText UWeaponWidget::GetWeaponName() const
{
	return Weapon->GetDisplayName();
}

FSlateColor UWeaponWidget::GetButtonBrush() const
{
	FLinearColor Color = FLinearColor::White;
	
	ABorderSecurityCharacter* Character = Cast<ABorderSecurityCharacter>(GetOwningPlayer()->GetPawn());
	if (Character && Character->GetSelectedWeapon() == Weapon)
	{
		Color.A = 1;
	}
	else
	{
		Color.A = 0.3f;
	}

	return Color;
}

void UWeaponWidget::LoadUpgrades()
{
	AUpgradeableWeapon* UpgradeableWeapon = Cast<AUpgradeableWeapon>(Weapon);
	if (!UpgradeableWeapon)
	{
		return;
	}

	for (FUpgradeInfo Upgrade : UpgradeableWeapon->GetAvailableUpgrades())
	{
		UWeaponUpgradeWidget* UpgradeWidget = CreateWidget<UWeaponUpgradeWidget>(GetOwningPlayer(), WeaponUpgradeClass);
		UpgradeWidget->SetWeapon(UpgradeableWeapon);
		UpgradeWidget->SetUpgrade(Upgrade);

		UPanelSlot* PanelSlot = Cast<UPanelSlot>(GetUpgradeBox()->AddChild(UpgradeWidget));
		//Slot->SetHorizontalAlignment(HAlign_Fill);
		//Slot->SetVerticalAlignment(VAlign_Bottom);
	}
}

void UWeaponWidget::OnWeaponClicked()
{
	// Select weapon
	ABorderSecurityCharacter* Character = Cast<ABorderSecurityCharacter>(GetOwningPlayer()->GetPawn());
	if (Character)
	{
		Character->SelectWeapon(Weapon);
	}
}