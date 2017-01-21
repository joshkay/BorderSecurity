// Josh Kay 2015

#include "BorderSecurity.h"
#include "MainMenuHUD.h"

void AMainMenuHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ShowMainMenu();
}

void AMainMenuHUD::Destroyed()
{
	Super::Destroyed();

	HideMainMenu();
	HideHelp();
}

void AMainMenuHUD::ShowMainMenu()
{
	HideHelp();
	HideCredits();

	APlayerController* OwningController = GetOwningPlayerController();
	if (OwningController)
	{
		if (MainMenuClass)
		{
			MainMenuWidget = CreateWidget<UMainMenuWidget>(OwningController, MainMenuClass);

			if (MainMenuWidget)
			{
				MainMenuWidget->AddToViewport();
			}
		}
	}
}

void AMainMenuHUD::HideMainMenu()
{
	if (MainMenuWidget)
	{
		MainMenuWidget->RemoveFromViewport();
		MainMenuWidget = NULL;
	}
}

void AMainMenuHUD::ShowHelp()
{
	HideMainMenu();

	APlayerController* OwningController = GetOwningPlayerController();
	if (OwningController)
	{
		if (HelpClass)
		{
			HelpWidget = CreateWidget<UInfoWidget>(OwningController, HelpClass);

			if (HelpWidget)
			{
				HelpWidget->AddToViewport();
			}
		}
	}
}

void AMainMenuHUD::HideHelp()
{
	if (HelpWidget)
	{
		HelpWidget->RemoveFromViewport();
		HelpWidget = NULL;
	}
}

void AMainMenuHUD::ShowCredits()
{
	HideMainMenu();

	APlayerController* OwningController = GetOwningPlayerController();
	if (OwningController)
	{
		if (CreditsClass)
		{
			CreditsWidget = CreateWidget<UInfoWidget>(OwningController, CreditsClass);

			if (CreditsWidget)
			{
				CreditsWidget->AddToViewport();
			}
		}
	}
}

void AMainMenuHUD::HideCredits()
{
	if (CreditsWidget)
	{
		CreditsWidget->RemoveFromViewport();
		CreditsWidget = NULL;
	}
}