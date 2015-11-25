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

	virtual void BeginPlay() override;

	void DealDamage(float Amount);

	FORCEINLINE float GetHealth() { return Health; }
	FORCEINLINE bool IsAlive() { return Health > 0.f; }

protected:
	UPROPERTY(EditAnywhere, Category = Collision)
	UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = Health)
	float StartingHealth;

	float Health;
};
