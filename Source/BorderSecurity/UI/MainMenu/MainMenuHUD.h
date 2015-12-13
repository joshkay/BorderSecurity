// Josh Kay 2015

#pragma once

#include "GameFramework/HUD.h"
#include "Widgets/MainMenuWidget.h"
#include "Widgets/InfoWidget.h"
#include "MainMenuHUD.generated.h"

UCLASS()
class BORDERSECURITY_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void PostInitializeComponents() override;
	void Destroyed() override;

	void ShowMainMenu();
	void HideMainMenu();

	void ShowHelp();
	void HideHelp();

	void ShowCredits();
	void HideCredits();

protected:
	UPROPERTY(EditAnywhere, Category = Widgets)
	TSubclassOf<UMainMenuWidget> MainMenuClass;

	UPROPERTY(EditAnywhere, Category = Widgets)
	TSubclassOf<UInfoWidget> HelpClass;

	UPROPERTY(EditAnywhere, Category = Widgets)
	TSubclassOf<UInfoWidget> CreditsClass;

	UMainMenuWidget* MainMenuWidget;
	UInfoWidget* HelpWidget;
	UInfoWidget* CreditsWidget;
};
