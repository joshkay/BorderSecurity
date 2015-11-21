// Josh Kay 2015

#pragma once

#include "GameFramework/Actor.h"
#include "BorderItem.generated.h"

UCLASS()
class BORDERSECURITY_API ABorderItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ABorderItem();

protected:
	UPROPERTY(EditAnywhere, Category = Collision)
	UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* Mesh;
	
};
