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

	APlayerController* Owner = GetOwningPlayerController();
	if (Owner)
	{
		if (MainMenuClass)
		{
			MainMenuWidget = CreateWidget<UMainMenuWidget>(Owner, MainMenuClass);

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

	APlayerController* Owner = GetOwningPlayerController();
	if (Owner)
	{
		if (HelpClass)
		{
			HelpWidget = CreateWidget<UInfoWidget>(Owner, HelpClass);

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

	APlayerController* Owner = GetOwningPlayerController();
	if (Owner)
	{
		if (CreditsClass)
		{
			CreditsWidget = CreateWidget<UInfoWidget>(Owner, CreditsClass);

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