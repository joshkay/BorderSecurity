// Josh Kay 2015

#include "BorderSecurity.h"
#include "BorderSecurityHUD.h"

void ABorderSecurityHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	APlayerController* Owner = GetOwningPlayerController();
	if (Owner)
	{
		if (MoneyClass)
		{
			MoneyWidget = CreateWidget<UMoneyWidget>(Owner, MoneyClass);

			if (MoneyWidget)
			{
				MoneyWidget->AddToViewport();
			}
		}

		if (BorderHealthClass)
		{
			BorderHealthWidget = CreateWidget<UBorderHealthWidget>(Owner, BorderHealthClass);

			if (BorderHealthWidget)
			{
				BorderHealthWidget->AddToViewport(1.f);
			}
		}
	}
}

void ABorderSecurityHUD::Destroyed()
{
	Super::Destroyed();

	if (MoneyWidget)
	{
		MoneyWidget->RemoveFromViewport();
		MoneyWidget = NULL;
	}
	if (BorderHealthWidget)
	{
		BorderHealthWidget->RemoveFromViewport();
		BorderHealthWidget = NULL;
	}
}

void ABorderSecurityHUD::AddHealthBar(AActor* Owner)
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController)
	{
		UHealthBarWidget* HealthBar = HealthBarWidgets.FindOrAdd(Owner);
		if (!HealthBar)
		{
			if (HealthBarClass)
			{
				HealthBar = CreateWidget<UHealthBarWidget>(PlayerController, HealthBarClass);
			}

			if (HealthBar)
			{
				HealthBar->SetOwner(Owner);

				HealthBar->AddToViewport();
				HealthBarWidgets[Owner] = HealthBar;
			}
		}
	}
}

void ABorderSecurityHUD::RemoveHealthBar(AActor* Owner)
{
	if (!HealthBarWidgets.Contains(Owner))
	{
		return;
	}

	UHealthBarWidget* HealthBar = *HealthBarWidgets.Find(Owner);
	APlayerController* PlayerController = GetOwningPlayerController();

	if (HealthBar && PlayerController)
	{
		HealthBar->RemoveFromViewport();
		HealthBar = NULL;

		HealthBarWidgets.Remove(Owner);
	}
}

void ABorderSecurityHUD::AddMoneyNotification(AActor* Owner, int32 Amount)
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController)
	{
		UMoneyNotificationWidget* MoneyNotification = MoneyNotificationWidgets.FindOrAdd(Owner);
		if (!MoneyNotification)
		{
			if (MoneyNotificationClass)
			{
				MoneyNotification = CreateWidget<UMoneyNotificationWidget>(PlayerController, MoneyNotificationClass);
			}

			if (MoneyNotification)
			{
				MoneyNotification->SetOwner(Owner);
				MoneyNotification->SetMoney(Amount);
				MoneyNotification->OnNotificationComplete(FSimpleDelegate::CreateUObject(this, &ABorderSecurityHUD::RemoveMoneyNotification, Owner));

				MoneyNotification->AddToViewport();
				MoneyNotificationWidgets[Owner] = MoneyNotification;
			}
		}
	}
}

void ABorderSecurityHUD::RemoveMoneyNotification(AActor* Owner)
{
	if (!MoneyNotificationWidgets.Contains(Owner))
	{
		return;
	}

	UMoneyNotificationWidget* MoneyNotification = *MoneyNotificationWidgets.Find(Owner);
	APlayerController* PlayerController = GetOwningPlayerController();

	if (MoneyNotification && PlayerController)
	{
		MoneyNotification->RemoveFromViewport();
		MoneyNotification = NULL;

		MoneyNotificationWidgets.Remove(Owner);
	}
}