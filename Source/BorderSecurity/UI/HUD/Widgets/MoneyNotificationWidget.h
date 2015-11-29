// Josh Kay 2015

#pragma once

#include "Blueprint/UserWidget.h"
#include "MoneyNotificationWidget.generated.h"

UCLASS()
class BORDERSECURITY_API UMoneyNotificationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	FORCEINLINE void SetOwner(AActor* NewOwner) { Owner = NewOwner; }
	FORCEINLINE void SetMoney(int32 NewMoney) { Money = NewMoney; }

	void OnNotificationComplete(FSimpleDelegate Callback) { NotificationCompleteDelegate = Callback; }

protected:
	UFUNCTION(BlueprintCallable, Category = MoneyNotification)
	virtual ESlateVisibility GetVisibility() const;
	UFUNCTION(BlueprintCallable, Category = MoneyNotification)
	virtual FSlateColor GetColorAndOpacitiy() const;
	UFUNCTION(BlueprintCallable, Category = MoneyNotification)
	virtual FVector2D GetCurrentPosition() const;
	UFUNCTION(BlueprintCallable, Category = MoneyNotification)
	virtual FText GetMoneyText() const;

	float GetDisplayedPercentage() const;

	UPROPERTY(EditAnywhere, Category = Time)
	float TimeToDisplay;

	float TimeDisplayed;

	AActor* Owner;
	int32 Money;

	FSimpleDelegate NotificationCompleteDelegate;
};
