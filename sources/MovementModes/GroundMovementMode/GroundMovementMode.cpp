#include "GroundMovementMode.h"

GroundMovementMode::GroundMovementMode(float InAcceleration, float InDeceleration, float InTopSpeed)
	: MovementModeBase(InAcceleration, InDeceleration, InTopSpeed)
{
}

bool GroundMovementMode::CanSwitchToMode(EMovementMode CurrentMovementMode, const Vector3& CurrentVelocity) const
{
	return FloatEquals(CurrentVelocity.y, 0.0f) && MovementModeBase::CanSwitchToMode(CurrentMovementMode, CurrentVelocity);
}
