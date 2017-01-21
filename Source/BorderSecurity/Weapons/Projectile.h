// Josh Kay 2015

#pragma once

#include "GameFramework/Actor.h"
#include "ThrownMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BORDERSECURITY_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

	void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	void AddIgnoredActor(AActor* IgnoredActor);

	float GetDamage();

	virtual void UpgradeDamage(float Amount);
	virtual void UpgradeSpeed(float Amount);

protected:
	UFUNCTION()
	void TimeIsUp();

	void ApplyDamage(AActor* Actor);
	virtual void DestroyProjectile();

	// Box collider on projectile
	UPROPERTY(EditAnywhere, Category = Collision)
	USphereComponent* ColliderComponent;

	// Mesh for projectile
	//UPROPERTY(VisibleAnywhere, Category = Mesh)
	//UMeshComponent* MeshComponent;

	// Movement
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UThrownMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, Category = Movement)
	float TimeToDestroy;

	// Damage
	UPROPERTY(EditAnywhere, Category = Damage)
	float Damage;

	UPROPERTY(EditAnywhere, Category = Damage)
	bool bDestroyOnCollision;

	TArray<AActor*> IgnoredActors;
	FTimerHandle DestroyTimer;
};
