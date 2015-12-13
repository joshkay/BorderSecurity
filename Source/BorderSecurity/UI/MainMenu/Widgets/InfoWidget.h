// Josh Kay 2015

#pragma once

#include "Blueprint/UserWidget.h"
#include "InfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class BORDERSECURITY_API UInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Help)
	UButton* GetBackButton();
	
	UFUNCTION()
	void OnBackClicked();
};
