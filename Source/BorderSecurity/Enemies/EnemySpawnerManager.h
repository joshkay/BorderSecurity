// Josh Kay 2015

#pragma once

#include "GameFramework/Actor.h"
#include "EnemySpawner.h"
#include "EnemySpawnerManager.generated.h"

UCLASS()
class BORDERSECURITY_API AEnemySpawnerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySpawnerManager();

	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void OnSpawn();

	UPROPERTY(EditAnywhere, Category = Spawning)
	float SpawnTime;

	TArray<AEnemySpawner*> Spawners;

	FTimerHandle SpawnTimerHandle;
};