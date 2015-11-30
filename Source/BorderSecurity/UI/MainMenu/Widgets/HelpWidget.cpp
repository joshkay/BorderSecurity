// Josh Kay 2015

#include "BorderSecurity.h"
#include "HelpWidget.h"

void UHelpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GetBackButton()->OnClicked.AddDynamic(this, &UHelpWidget::OnHelpClicked);
}

void UHelpWidget::OnHelpClicked()
{
	AMainMenuHUD* HUD = Cast<AMainMenuHUD>(GetOwningPlayer()->GetHUD());
	if (HUD)
	{
		HUD->ShowMainMenu();
	}
}