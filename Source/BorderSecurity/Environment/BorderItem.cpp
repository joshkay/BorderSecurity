// Josh Kay 2015

#include "BorderSecurity.h"
#include "BorderItem.h"

ABorderItem::ABorderItem()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->AttachTo(RootComponent);
}

void ABorderItem::BeginPlay()
{
	Super::BeginPlay();

	Health = StartingHealth;
}

void ABorderItem::DealDamage(float Amount)
{
	Health -= Amount;
	if (Health <= 0.f)
	{
		Destroy();
	}
}