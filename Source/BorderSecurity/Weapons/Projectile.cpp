// Josh Kay 2015

#include "BorderSecurity.h"
#include "Environment/BorderItem.h"
#include "Projectile.h"

AProjectile::AProjectile()
{
	//PrimaryActorTick.bCanEverTick = true;	
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	ColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ColliderComponent"));
	ColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlap);
	ColliderComponent->AttachTo(RootComponent);

	MovementComponent = CreateDefaultSubobject<UThrownMovementComponent>(TEXT("MovementComponent"));
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	AddIgnoredActor(Instigator);
	AddIgnoredActor(GetOwner());

	GetWorldTimerManager().SetTimer(DestroyTimer, this, &AProjectile::TimeIsUp, TimeToDestroy, false);
}

void AProjectile::OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!IgnoredActors.Contains(OtherActor))
	{
		ApplyDamage(OtherActor);
		
		if (bDestroyOnCollision)
		{
			Destroy(true);
		}
	}
}

void AProjectile::AddIgnoredActor(AActor* IgnoredActor)
{
	IgnoredActors.Add(IgnoredActor);
}

float AProjectile::GetDamage()
{
	return Damage;
}

void AProjectile::TimeIsUp()
{
	Destroy();
}

void AProjectile::ApplyDamage(AActor* Actor)
{
	if (Actor)
	{
		UGameplayStatics::ApplyDamage(Actor, GetDamage(), Instigator->GetController(), GetOwner(), UDamageType::StaticClass());
	}
}
