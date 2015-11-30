// Josh Kay 2015

#include "BorderSecurity.h"
#include "MainMenuWidget.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GetPlayButton()->OnClicked.AddDynamic(this, &UMainMenuWidget::OnPlayClicked);
	GetHelpButton()->OnClicked.AddDynamic(this, &UMainMenuWidget::OnHelpClicked);
	GetQuitButton()->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);
}

void UMainMenuWidget::OnPlayClicked()
{
	UGameplayStatics::OpenLevel(this, PlayLevelName, false, FString());
}

void UMainMenuWidget::OnHelpClicked()
{
	AMainMenuHUD* HUD = Cast<AMainMenuHUD>(GetOwningPlayer()->GetHUD());
	if (HUD)
	{
		HUD->ShowHelp();
	}
}

void UMainMenuWidget::OnQuitClicked()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}