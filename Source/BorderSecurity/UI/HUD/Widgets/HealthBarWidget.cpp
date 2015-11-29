// Josh Kay 2015

#include "BorderSecurity.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"
#include "Player/BorderSecurityCharacter.h"
#include "HealthBarWidget.h"

ESlateVisibility UHealthBarWidget::GetVisibility() const
{
	return ESlateVisibility::Visible;
}

FVector2D UHealthBarWidget::GetCurrentPosition() const
{
	FVector2D ScreenLocation = FVector2D::ZeroVector;

	if (Owner && GetOwningPlayer())
	{
		UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetOwningPlayer(), Owner->GetActorLocation(), ScreenLocation);
	}

	// position above character
	ScreenLocation.Y -= 100.f * UWidgetLayoutLibrary::GetViewportScale(GetWorld());

	return ScreenLocation;
}

float UHealthBarWidget::GetHealthPercentage() const
{
	float Health;

	ABorderSecurityCharacter* BSCharacter = Cast<ABorderSecurityCharacter>(Owner);
	if (BSCharacter)
	{
		Health = BSCharacter->GetHealthComponent()->GetHPPercent();
	}

	return Health;
}

float UHealthBarWidget::GetArmorPercentage() const
{
	float Armor;

	ABorderSecurityCharacter* BSCharacter = Cast<ABorderSecurityCharacter>(Owner);
	if (BSCharacter)
	{
		Armor = BSCharacter->GetHealthComponent()->GetArmorPercent();
	}

	return Armor;
}

ESlateVisibility UHealthBarWidget::GetArmorVisibility() const
{
	ABorderSecurityCharacter* BSCharacter = Cast<ABorderSecurityCharacter>(Owner);
	if (BSCharacter)
	{
		if (BSCharacter->GetHealthComponent()->GetMaxArmor() <= 0.f)
		{
			return ESlateVisibility::Hidden;
		}
	}

	return ESlateVisibility::Visible;
}