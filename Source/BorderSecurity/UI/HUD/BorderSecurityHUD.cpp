// Josh Kay 2015

#include "BorderSecurity.h"
#include "BorderSecurityHUD.h"

void ABorderSecurityHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	APlayerController* OwningController = GetOwningPlayerController();
	if (OwningController)
	{
		if (MoneyClass)
		{
			MoneyWidget = CreateWidget<UMoneyWidget>(OwningController, MoneyClass);

			if (MoneyWidget)
			{
				MoneyWidget->AddToViewport();
			}
		}

		if (BorderHealthClass)
		{
			BorderHealthWidget = CreateWidget<UBorderHealthWidget>(OwningController, BorderHealthClass);

			if (BorderHealthWidget)
			{
				BorderHealthWidget->AddToViewport(1.f);
			}
		}

		if (WeaponHolderClass)
		{
			WeaponHolderWidget = CreateWidget<UWeaponHolderWidget>(OwningController, WeaponHolderClass);

			if (WeaponHolderWidget)
			{
				WeaponHolderWidget->AddToViewport();
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
	if (WeaponHolderWidget)
	{
		WeaponHolderWidget->RemoveFromViewport();
		WeaponHolderWidget = NULL;
	}
}

void ABorderSecurityHUD::AddHealthBar(AActor* OwningActor)
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController)
	{
		UHealthBarWidget* HealthBar = HealthBarWidgets.FindOrAdd(OwningActor);
		if (!HealthBar)
		{
			if (HealthBarClass)
			{
				HealthBar = CreateWidget<UHealthBarWidget>(PlayerController, HealthBarClass);
			}

			if (HealthBar)
			{
				HealthBar->SetOwner(OwningActor);

				HealthBar->AddToViewport();
				HealthBarWidgets[OwningActor] = HealthBar;
			}
		}
	}
}

void ABorderSecurityHUD::RemoveHealthBar(AActor* OwningActor)
{
	if (!HealthBarWidgets.Contains(OwningActor))
	{
		return;
	}

	UHealthBarWidget* HealthBar = *HealthBarWidgets.Find(OwningActor);
	APlayerController* PlayerController = GetOwningPlayerController();

	if (HealthBar && PlayerController)
	{
		HealthBar->RemoveFromViewport();
		HealthBar = NULL;

		HealthBarWidgets.Remove(OwningActor);
	}
}

void ABorderSecurityHUD::AddMoneyNotification(AActor* OwningActor, int32 Amount)
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController)
	{
		UMoneyNotificationWidget* MoneyNotification = MoneyNotificationWidgets.FindOrAdd(OwningActor);
		if (!MoneyNotification)
		{
			if (MoneyNotificationClass)
			{
				MoneyNotification = CreateWidget<UMoneyNotificationWidget>(PlayerController, MoneyNotificationClass);
			}

			if (MoneyNotification)
			{
				MoneyNotification->SetOwner(OwningActor);
				MoneyNotification->SetMoney(Amount);
				MoneyNotification->OnNotificationComplete(FSimpleDelegate::CreateUObject(this, &ABorderSecurityHUD::RemoveMoneyNotification, OwningActor));

				MoneyNotification->AddToViewport();
				MoneyNotificationWidgets[OwningActor] = MoneyNotification;
			}
		}
	}
}

void ABorderSecurityHUD::RemoveMoneyNotification(AActor* OwningActor)
{
	if (!MoneyNotificationWidgets.Contains(OwningActor))
	{
		return;
	}

	UMoneyNotificationWidget* MoneyNotification = *MoneyNotificationWidgets.Find(OwningActor);
	APlayerController* PlayerController = GetOwningPlayerController();

	if (MoneyNotification && PlayerController)
	{
		MoneyNotification->RemoveFromViewport();
		MoneyNotification = NULL;

		MoneyNotificationWidgets.Remove(OwningActor);
	}
}

void ABorderSecurityHUD::AddWeapon(AWeapon* Weapon)
{
	if (WeaponHolderWidget)
	{
		WeaponHolderWidget->AddWeapon(Weapon);
	}
}