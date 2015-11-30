// Josh Kay 2015

#pragma once

#include "GameFramework/HUD.h"
#include "Widgets/MainMenuWidget.h"
#include "Widgets/HelpWidget.h"
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

protected:
	UPROPERTY(EditAnywhere, Category = Widgets)
	TSubclassOf<UMainMenuWidget> MainMenuClass;

	UPROPERTY(EditAnywhere, Category = Widgets)
	TSubclassOf<UHelpWidget> HelpClass;

	UMainMenuWidget* MainMenuWidget;
	UHelpWidget* HelpWidget;
};
