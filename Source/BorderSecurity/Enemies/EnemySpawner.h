// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class BORDERSECURITY_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySpawner();

	UFUNCTION()
	void SpawnEnemy();

protected:

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//UBoxComponent* SpawnArea;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AActor>> SpawnableActors;
};