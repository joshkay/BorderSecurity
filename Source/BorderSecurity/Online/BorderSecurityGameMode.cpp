// Fill out your copyright notice in the Description page of Project Settings.

#include "BorderSecurity.h"
#include "Player/BorderSecurityPlayerController.h"
#include "BorderSecurityGameMode.h"

ABorderSecurityGameMode::ABorderSecurityGameMode()
	: Super()
{
	// Load in character class
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<UBlueprint> CharacterClass;
		FConstructorStatics()
			: CharacterClass(TEXT("Blueprint'/Game/Blueprints/Officer.Officer'"))
		{
		}
	};

	static FConstructorStatics ConstructorStatics;

	if (ConstructorStatics.CharacterClass.Object)
	{
		DefaultPawnClass = Cast<UClass>(ConstructorStatics.CharacterClass.Object->GeneratedClass);
	}

	// Set default player controller
	PlayerControllerClass = ABorderSecurityPlayerController::StaticClass();
}