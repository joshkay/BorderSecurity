// Josh Kay 2015

#include "BorderSecurity.h"
#include "BorderTower.h"

ABorderTower::ABorderTower(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCapsuleComponent>(TEXT("ColliderComponent")))
{
	PlayerLocationComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerLocationComponent"));
	PlayerLocationComponent->AttachTo(RootComponent);
}

void ABorderTower::Destroyed()
{
	Super::Destroyed();

	for (TActorIterator<ABorderTower> BorderActorItr(GetWorld()); BorderActorItr; ++BorderActorItr)
	{
		ABorderTower* BorderItem = *BorderActorItr;
		if (BorderItem && BorderItem != this)
		{
			return;
		}
	}

	UGameplayStatics::OpenLevel(this, TEXT("/Game/Maps/MainMenu"), false, FString());
}

FVector ABorderTower::GetPlayerLocation()
{
	return PlayerLocationComponent->GetComponentLocation();
}
