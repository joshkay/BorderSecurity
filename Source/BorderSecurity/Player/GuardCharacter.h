// Josh Kay 2015

#pragma once

#include "GameFramework/Character.h"
#include "BorderSecurityCharacter.h"
#include "GuardCharacter.generated.h"

UCLASS()
class BORDERSECURITY_API AGuardCharacter : public ABorderSecurityCharacter
{
	GENERATED_BODY()

public:
	AGuardCharacter();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void StartFire() override;
	void StopFire() override;

	FORCEINLINE float GetTurnSpeed() { return TurnSpeed; }
	
protected:
	UFUNCTION()
	float GetRotationFromMouse();

	UFUNCTION()
	void TurnRight(float Scale);

	// Update rotation based on mouse location
	void UpdateRotation();
	
	// Speed to turn the character / camera at edge of screen
	float TurnSpeed;

	// Area to strart turning
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ScreenTurnArea;

	// Max amount to turn to the right
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxRightTurn;

	// Max amount to turn to the left
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxLeftTurn;

	// Camera boom
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* CameraBoom;

	// Camera attached to player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* Camera;
};
