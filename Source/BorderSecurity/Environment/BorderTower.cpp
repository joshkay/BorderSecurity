// Josh Kay 2015

#include "BorderSecurity.h"
#include "BorderTower.h"

ABorderTower::ABorderTower(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCapsuleComponent>(TEXT("ColliderComponent")))
{
	PlayerLocationComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerLocationComponent"));
	PlayerLocationComponent->AttachTo(RootComponent);
}

FVector ABorderTower::GetPlayerLocation()
{
	return PlayerLocationComponent->GetComponentLocation();
}
