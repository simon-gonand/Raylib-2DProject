#include "GrapplingBalanceMovementMode.h"

GrapplingBalanceMovementMode::GrapplingBalanceMovementMode(float InAcceleration, float InDeceleration, float InTopSpeed)
	: MovementModeBase(InAcceleration, InDeceleration, InTopSpeed)
{
}

bool GrapplingBalanceMovementMode::CanSwitchToMode(EMovementMode PreviousMovementMode, const Vector3& CurrentVelocity) const
{
	return MovementModeBase::CanSwitchToMode(PreviousMovementMode, CurrentVelocity) && PreviousMovementMode != EMovementMode::THROWN;
}
