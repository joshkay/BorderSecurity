// Josh Kay 2015

#pragma once

#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "BorderItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class BORDERSECURITY_API UBorderItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

	FORCEINLINE void SetOwner(AActor* NewOwner) { Owner = NewOwner; }

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = BorderItem)
	USizeBox* GetSizeBox();

	UFUNCTION(BlueprintCallable, Category = BorderItem)
	virtual ESlateVisibility GetVisibility() const;
	UFUNCTION(BlueprintCallable, Category = BorderItem)
	virtual FSlateColor GetHealthColor() const;

	UFUNCTION(BlueprintCallable, Category = BorderItem)
	virtual float GetHealthPercentage() const;
	UFUNCTION(BlueprintCallable, Category = BorderItem)
	virtual float GetArmorPercentage() const;

	UFUNCTION(BlueprintCallable, Category = BorderItem)
	virtual ESlateVisibility GetArmorVisibility() const;

	AActor* Owner;	
};