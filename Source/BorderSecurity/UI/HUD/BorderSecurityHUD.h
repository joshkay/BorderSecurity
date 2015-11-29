// Josh Kay 2015

#pragma once

#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/MoneyWidget.h"
#include "Widgets/MoneyNotificationWidget.h"
#include "Widgets/HealthBarWidget.h"
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

	void AddHealthBar(AActor* Owner);
	void RemoveHealthBar(AActor* Owner);

	void AddMoneyNotification(AActor* Owner, int32 Amount);
	void RemoveMoneyNotification(AActor* Owner);

protected:
	UPROPERTY(EditAnywhere, Category = Widgets)
	TSubclassOf<UMoneyWidget> MoneyClass;

	UPROPERTY(EditAnywhere, Category = Widgets)
	TSubclassOf<UMoneyNotificationWidget> MoneyNotificationClass;

	UPROPERTY(EditAnywhere, Category = Widgets)
	TSubclassOf<UHealthBarWidget> HealthBarClass;
	
	UMoneyWidget* MoneyWidget;
	TMap<AActor*, UMoneyNotificationWidget*> MoneyNotificationWidgets;
	TMap<AActor*, UHealthBarWidget*> HealthBarWidgets;
};
