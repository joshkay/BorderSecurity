// Josh Kay 2015

#include "BorderSecurity.h"
#include "ThrownMovementComponent.h"

void UThrownMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// Store initial rotation
	CurrentRotation = GetOwner()->GetActorRotation();
}

void UThrownMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Update current projectile rotation
	UpdateRotation();
}

void UThrownMovementComponent::UpdateRotation()
{
	// Rotate around the yaw
	CurrentRotation.Pitch -= RotationSpeed;

	GetOwner()->SetActorRotation(CurrentRotation);
}
