// Josh Kay 2015

#include "BorderSecurity.h"
#include "EnemySpawnerManager.h"

AEnemySpawnerManager::AEnemySpawnerManager()
{

}

void AEnemySpawnerManager::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AEnemySpawner> EnemySpawnerItr(GetWorld()); EnemySpawnerItr; ++EnemySpawnerItr)
	{
		AEnemySpawner* EnemySpawner = *EnemySpawnerItr;
		if (EnemySpawner)
		{
			Spawners.Add(EnemySpawner);
		}
	}

	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemySpawnerManager::OnSpawn, SpawnTime, true, 0.f);
}

void AEnemySpawnerManager::OnSpawn()
{
	for (AEnemySpawner* Spawner : Spawners)
	{
		Spawner->SpawnEnemy();
	}
}