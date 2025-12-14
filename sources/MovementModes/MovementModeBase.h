#pragma once

#include "../Components/Movements/MovementComponent.h"


#include <raylib.h>

class MovementModeBase
{
public:
	MovementModeBase(float InAcceleration, float InDeceleration, float InTopSpeed);

	virtual bool CanSwitchToMode(EMovementMode CurrentMovementMode) const;
	virtual void OnSwitch() {}
	virtual Vector3 PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity);

protected:
	float Acceleration;
	float Deceleration;
	float DeaccelerateAlpha;

	float TopSpeed;

	static Vector3 LastVelocityIncrease; // Need to be shared to all MovementModeBase instances
};