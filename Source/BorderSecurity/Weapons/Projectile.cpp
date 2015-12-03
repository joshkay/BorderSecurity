// Josh Kay 2015

#include "BorderSecurity.h"
#include "Environment/BorderItem.h"
#include "Projectile.h"

AProjectile::AProjectile()
{
	//MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	//RootComponent = MeshComponent;

	ColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ColliderComponent"));
	ColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlap);
	RootComponent = ColliderComponent;

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
			DestroyProjectile();
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

void AProjectile::UpgradeDamage(float Amount)
{
	Damage *= Amount;
}

void AProjectile::UpgradeSpeed(float Amount)
{
	MovementComponent->InitialSpeed *= Amount;
}

void AProjectile::TimeIsUp()
{
	DestroyProjectile();
}

void AProjectile::ApplyDamage(AActor* Actor)
{
	if (Actor && Instigator)
	{
		UGameplayStatics::ApplyDamage(Actor, GetDamage(), Instigator->GetController(), GetOwner(), UDamageType::StaticClass());
	}
}

void AProjectile::DestroyProjectile()
{
	Destroy(true);
}