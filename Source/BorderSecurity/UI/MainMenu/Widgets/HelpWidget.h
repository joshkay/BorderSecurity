// Josh Kay 2015

#pragma once

#include "Blueprint/UserWidget.h"
#include "HelpWidget.generated.h"

/**
 * 
 */
UCLASS()
class BORDERSECURITY_API UHelpWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Help)
	UButton* GetBackButton();
	
	UFUNCTION()
	void OnHelpClicked();
};
