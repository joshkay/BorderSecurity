// Josh Kay 2015

#pragma once

#include "GameFramework/Actor.h"
#include "Components/HealthComponent.h"
#include "BorderItem.generated.h"

UCLASS()
class BORDERSECURITY_API ABorderItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ABorderItem(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	FORCEINLINE UHealthComponent* GetHealthComponent() { return HealthComponent; }

protected:
	UPROPERTY(EditAnywhere, Category = Collision)
	USceneComponent* ColliderComponent;

	UPROPERTY(EditAnywhere, Category = MeshComponent)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = HP)
	UHealthComponent* HealthComponent;
};
