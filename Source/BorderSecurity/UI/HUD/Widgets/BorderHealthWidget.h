// Josh Kay 2015

#pragma once

#include "Blueprint/UserWidget.h"
#include "BorderItemWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "BorderHealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class BORDERSECURITY_API UBorderHealthWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = BorderItem)
	UHorizontalBox* GetHorizontalBox();

protected:
	UPROPERTY(EditAnywhere, Category = BorderItem)
	TSubclassOf<UBorderItemWidget> BorderItemClass;
};
