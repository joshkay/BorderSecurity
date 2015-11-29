// Josh Kay 2015

#include "BorderSecurity.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"
#include "MoneyNotificationWidget.h"

void UMoneyNotificationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TimeDisplayed = 0.f;
}

void UMoneyNotificationWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	TimeDisplayed += InDeltaTime;

	if (TimeDisplayed >= TimeToDisplay)
	{
		NotificationCompleteDelegate.ExecuteIfBound();
	}
}

ESlateVisibility UMoneyNotificationWidget::GetVisibility() const
{
	return ESlateVisibility::Visible;
}

FSlateColor UMoneyNotificationWidget::GetColorAndOpacitiy() const
{
	FLinearColor Color = FLinearColor::White;
	Color.A = 1.f - GetDisplayedPercentage();

	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::White, FString::Printf(TEXT("DISPLAYED: %f"), Color.A));

	return FSlateColor(Color);
}

FVector2D UMoneyNotificationWidget::GetCurrentPosition() const
{
	FVector2D ScreenLocation = FVector2D::ZeroVector;

	if (Owner && GetOwningPlayer())
	{
		UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetOwningPlayer(), Owner->GetActorLocation(), ScreenLocation);
	}

	// position above character
	ScreenLocation.Y -= 100.f * UWidgetLayoutLibrary::GetViewportScale(GetWorld());

	// slowly rise above
	ScreenLocation.Y -= (200.f * UWidgetLayoutLibrary::GetViewportScale(GetWorld())) * (GetDisplayedPercentage());

	return ScreenLocation;
}

FText UMoneyNotificationWidget::GetMoneyText() const
{
	return FText::AsNumber(Money);
}

float UMoneyNotificationWidget::GetDisplayedPercentage() const
{
	return TimeDisplayed / TimeToDisplay;
}
