#include "GrapplingThrownMovementMode.h"

GrapplingThrownMovementMode::GrapplingThrownMovementMode(std::shared_ptr<PhysicsComponent> OwnerPhysicsComponent, std::shared_ptr<MovementComponent> OwnerMovementComp)
	: ThrownMovementMode(OwnerPhysicsComponent, OwnerMovementComp)
{
}

void GrapplingThrownMovementMode::OnSwitch()
{
	// We don't want to override the friction on this movement mode
}

Vector3 GrapplingThrownMovementMode::PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity)
{
	if (FloatEquals(CurrentVelocity.y, 0.0f))
	{
		LastVelocityIncrease = CurrentVelocity;
		MovementComp->SwitchMovementMode(EMovementMode::GROUND);
	}
	else if (FloatEquals(CurrentVelocity.x, 0.0f))
	{
		LastVelocityIncrease = CurrentVelocity;
		MovementComp->SwitchMovementMode(EMovementMode::FALLING);
	}

	return ThrownMovementMode::PerformMovement(DeltaTime, Input, CurrentVelocity);
}
