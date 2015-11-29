// Josh Kay 2015

#pragma once

#include "Blueprint/UserWidget.h"
#include "MoneyWidget.generated.h"

/**
 * 
 */
UCLASS()
class BORDERSECURITY_API UMoneyWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable, Category = MoneyNotification)
	virtual FText GetMoneyText() const;
	
};
