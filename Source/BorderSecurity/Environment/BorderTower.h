// Josh Kay 2015

#pragma once

#include "Environment/BorderItem.h"
#include "BorderTower.generated.h"

/**
 * 
 */
UCLASS()
class BORDERSECURITY_API ABorderTower : public ABorderItem
{
	GENERATED_BODY()
	
public:
	ABorderTower(const FObjectInitializer& ObjectInitializer);

	FVector GetPlayerLocation();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	USceneComponent* PlayerLocationComponent;
};
