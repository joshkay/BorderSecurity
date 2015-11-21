// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "BorderSecurityPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BORDERSECURITY_API ABorderSecurityPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ABorderSecurityPlayerController();
	void BeginPlay() override;
	
};
