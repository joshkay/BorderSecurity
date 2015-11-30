// Josh Kay 2015

#pragma once

#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class BORDERSECURITY_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = MainMenu)
	UButton* GetPlayButton();

	UFUNCTION(BlueprintImplementableEvent, Category = MainMenu)
	UButton* GetHelpButton();

	UFUNCTION(BlueprintImplementableEvent, Category = MainMenu)
	UButton* GetQuitButton();

	UFUNCTION()
	void OnPlayClicked();
	
	UFUNCTION()
	void OnHelpClicked();

	UFUNCTION()
	void OnQuitClicked();

protected:
	UPROPERTY(EditAnywhere, Category = MainMenu)
	FName PlayLevelName;
};