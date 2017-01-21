// Josh Kay 2015

#pragma once

#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/MoneyWidget.h"
#include "Widgets/MoneyNotificationWidget.h"
#include "Widgets/HealthBarWidget.h"
#include "Widgets/WeaponHolderWidget.h"
#include "Widgets/BorderHealthWidget.h"
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
	void Destroyed() override;

	void AddHealthBar(AActor* OwningActor);
	void RemoveHealthBar(AActor* OwningActor);

	void AddMoneyNotification(AActor* OwningActor, int32 Amount);
	void RemoveMoneyNotification(AActor* OwningActor);

	void AddWeapon(AWeapon* Weapon);

protected:
	UPROPERTY(EditAnywhere, Category = Widgets)
	TSubclassOf<UMoneyWidget> MoneyClass;

	UPROPERTY(EditAnywhere, Category = Widgets)
	TSubclassOf<UMoneyNotificationWidget> MoneyNotificationClass;

	UPROPERTY(EditAnywhere, Category = Widgets)
	TSubclassOf<UHealthBarWidget> HealthBarClass;

	UPROPERTY(EditAnywhere, Category = Widgets)
	TSubclassOf<UBorderHealthWidget> BorderHealthClass;

	UPROPERTY(EditAnywhere, Category = Widgets)
	TSubclassOf<UWeaponHolderWidget> WeaponHolderClass;
	
	UMoneyWidget* MoneyWidget;
	UBorderHealthWidget* BorderHealthWidget;
	UWeaponHolderWidget* WeaponHolderWidget;

	TMap<AActor*, UMoneyNotificationWidget*> MoneyNotificationWidgets;
	TMap<AActor*, UHealthBarWidget*> HealthBarWidgets;
};
