// Josh Kay 2015

#include "BorderSecurity.h"
#include "BorderItem.h"

ABorderItem::ABorderItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	
	ColliderComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ColliderComponent"));
	ColliderComponent->AttachTo(RootComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void ABorderItem::BeginPlay()
{
	Super::BeginPlay();
}

float ABorderItem::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// Apply damage and destroy if not alive
	HealthComponent->TakeDamage(ActualDamage);
	if (!HealthComponent->IsAlive())
	{
		Destroy();
	}

	return ActualDamage;
}