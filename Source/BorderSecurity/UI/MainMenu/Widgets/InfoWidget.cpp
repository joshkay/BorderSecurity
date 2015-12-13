// Josh Kay 2015

#include "BorderSecurity.h"
#include "InfoWidget.h"

void UInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GetBackButton()->OnClicked.AddDynamic(this, &UInfoWidget::OnBackClicked);
}

void UInfoWidget::OnBackClicked()
{
	AMainMenuHUD* HUD = Cast<AMainMenuHUD>(GetOwningPlayer()->GetHUD());
	if (HUD)
	{
		HUD->ShowMainMenu();
	}
}