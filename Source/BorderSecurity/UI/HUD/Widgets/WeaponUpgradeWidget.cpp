// Josh Kay 2015

#include "BorderSecurity.h"
#include "Player/BorderSecurityPlayerState.h"
#include "WeaponUpgradeWidget.h"

void UWeaponUpgradeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//if (!GetUpgradeButton()->OnClicked.IsAlreadyBound(this, &UWeaponUpgradeWidget::OnUpgradeClicked))
	//{
	GetUpgradeButton()->OnClicked.AddDynamic(this, &UWeaponUpgradeWidget::OnUpgradeClicked);
	//}
}

void UWeaponUpgradeWidget::NativeDestruct()
{
	Super::NativeDestruct();

	GetUpgradeButton()->OnClicked.RemoveDynamic(this, &UWeaponUpgradeWidget::OnUpgradeClicked);
}

FText UWeaponUpgradeWidget::GetUpgradeText() const
{
	return WeaponUpgrade.DisplayName;
}

ESlateVisibility UWeaponUpgradeWidget::GetVisibility() const
{
	ABorderSecurityPlayerState* PlayerState = Cast<ABorderSecurityPlayerState>(GetOwningPlayer()->PlayerState);
	if (PlayerState && PlayerState->Money >= WeaponUpgrade.Cost)
	{
		return ESlateVisibility::Visible;
	}

	return ESlateVisibility::Hidden;
}

void UWeaponUpgradeWidget::OnUpgradeClicked()
{
	Weapon->Upgrade(WeaponUpgrade);
}