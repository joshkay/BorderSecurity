// Fill out your copyright notice in the Description page of Project Settings.

#include "BorderSecurity.h"
#include "EnemySpawner.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	RootComponent = SceneComponent;
}

void AEnemySpawner::SpawnEnemy()
{
	if (SpawnableActors.Num() > 0)
	{
		GetWorld()->SpawnActor<AActor>(SpawnableActors[0], GetActorLocation(), GetActorRotation());
	}
}