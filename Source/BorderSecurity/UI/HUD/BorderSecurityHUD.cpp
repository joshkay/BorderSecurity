// Josh Kay 2015

#include "BorderSecurity.h"
#include "BorderSecurityHUD.h"

void ABorderSecurityHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	APlayerController* Owner = GetOwningPlayerController();
	if (Owner)
	{
		if (HUDClass)
		{
			HUDWidget = CreateWidget<UUserWidget>(Owner, HUDClass);

			if (HUDWidget)
			{
				HUDWidget->AddToViewport();
			}
		}
	}
}