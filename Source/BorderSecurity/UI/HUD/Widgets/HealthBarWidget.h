// Josh Kay 2015

#pragma once

#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class BORDERSECURITY_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void SetOwner(AActor* NewOwner) { Owner = NewOwner; }

protected:
	UFUNCTION(BlueprintCallable, Category = HealthBar)
	virtual ESlateVisibility GetVisibility() const;
	UFUNCTION(BlueprintCallable, Category = HealthBar)
	virtual FVector2D GetCurrentPosition() const;

	UFUNCTION(BlueprintCallable, Category = HealthBar)
	virtual float GetHealthPercentage() const;
	UFUNCTION(BlueprintCallable, Category = HealthBar)
	virtual float GetArmorPercentage() const;

	UFUNCTION(BlueprintCallable, Category = HealthBar)
	virtual ESlateVisibility GetArmorVisibility() const;

	AActor* Owner;
};
