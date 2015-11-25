// Josh Kay 2015

#pragma once

#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "BorderSecurityHUD.generated.h"

/**
 * 
 */
UCLASS()
class BORDERSECURITY_API ABorderSecurityHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void PostInitializeComponents() override;

protected:
	UPROPERTY(EditAnywhere, Category = Widgets)
	TSubclassOf<UUserWidget> HUDClass;
	
	UUserWidget* HUDWidget;
};
