// Josh Kay 2015

#include "BorderSecurity.h"
#include "Environment/BorderTower.h"
#include "Environment/BorderWall.h"
#include "BorderItemWidget.h"

void UBorderItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ABorderItem* BorderItem = Cast<ABorderItem>(Owner);
	if (BorderItem)
	{
		GetSizeBox()->SetHeightOverride(BorderItem->GetHealthComponent()->GetMaxHP() * 0.2f);
	}
}

ESlateVisibility UBorderItemWidget::GetVisibility() const
{
	if (Owner)
	{
		ABorderItem* BorderItem = Cast<ABorderItem>(Owner);
		if (BorderItem)
		{
			if (!BorderItem->GetHealthComponent()->IsAlive())
			{
				return ESlateVisibility::Hidden;
			}
		}
	}
	
	return ESlateVisibility::Visible;
}

FSlateColor UBorderItemWidget::GetHealthColor() const
{
	float HP = GetHealthPercentage();
	
	FLinearColor HPColor = FMath::Lerp(FLinearColor::Red, FLinearColor::Green, HP);

	return FSlateColor(HPColor);
}

float UBorderItemWidget::GetHealthPercentage() const
{
	float Health = 0.f;

	if (Owner)
	{
		ABorderItem* BorderItem = Cast<ABorderItem>(Owner);
		if (BorderItem)
		{
			Health = BorderItem->GetHealthComponent()->GetHPPercent();
		}
	}

	return Health;
}

float UBorderItemWidget::GetArmorPercentage() const
{
	float Armor = 0.f;

	if (Owner)
	{
		ABorderItem* BorderItem = Cast<ABorderItem>(Owner);
		if (BorderItem)
		{
			Armor = BorderItem->GetHealthComponent()->GetArmorPercent();
		}
	}

	return Armor;
}

ESlateVisibility UBorderItemWidget::GetArmorVisibility() const
{
	if (Owner)
	{
		ABorderItem* BorderItem = Cast<ABorderItem>(Owner);
		if (BorderItem)
		{
			if (BorderItem->GetHealthComponent()->HasArmor())
			{
				return ESlateVisibility::Visible;
			}
		}
	}
	
	return ESlateVisibility::Hidden;
}
