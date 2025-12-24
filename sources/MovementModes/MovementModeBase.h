#pragma once

#include "../Components/Movements/MovementComponent.h"

#include <raylib.h>

class MovementModeBase
{
public:
	MovementModeBase(float InAcceleration, float InDeceleration, float InTopSpeed);

	virtual bool CanSwitchToMode(EMovementMode CurrentMovementMode, const Vector3& CurrentVelocity) const;
	virtual void OnSwitch();
	virtual Vector3 PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity);
	virtual void OnEndMovement() {}

	void Activate();
	void Deactivate();
	bool IsActive() const;

	float GetTopSpeed() const;

protected:
	float Acceleration;
	float Deceleration;
	float DeaccelerateAlpha;

	float TopSpeed;

	static Vector3 LastVelocityIncrease; // Need to be shared to all MovementModeBase instances

	bool bIsActive;
};