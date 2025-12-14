#include "GroundMovementMode.h"

#include <raymath.h>

GroundMovementMode::GroundMovementMode(float InAcceleration, float InDeceleration, float InTopSpeed):
	MovementModeBase(InAcceleration, InDeceleration, InTopSpeed)
{
}

bool GroundMovementMode::CanSwitchToMode(EMovementMode CurrentMovementMode) const
{
	return CurrentMovementMode != EMovementMode::SLIDING;
}