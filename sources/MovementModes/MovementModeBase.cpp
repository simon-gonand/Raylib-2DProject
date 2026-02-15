#include "MovementModeBase.h"

#include <iostream>
#include <raymath.h>

MovementModeBase::MovementModeBase(float InAcceleration, float InDeceleration, float InTopSpeed):
	Acceleration{InAcceleration}, Deceleration{InDeceleration}, TopSpeed{InTopSpeed}, bIsActive{true}
{
}

bool MovementModeBase::CanSwitchToMode(EMovementMode CurrentMovementMode, const Vector3& CurrentVelocity) const
{
	return IsActive();
}

void MovementModeBase::OnSwitch()
{
}

Vector3 MovementModeBase::PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity)
{
	float Magnitude = Vector2Length(Input);
	Vector3 Result = CurrentVelocity;
	if (Magnitude > 0.0f)
	{
		Result.x += (Input.x > 0.0f ? Acceleration : -Acceleration) * DeltaTime;
	}
	else if (!FloatEquals(Result.x, 0.0f))
	{
		Result.x += (Result.x > 0.0f ? -Deceleration : Deceleration) * DeltaTime;

		if (CurrentVelocity.x * Result.x < 0.0f) // Set Velocity to 0 if CurrentVelocity.x & Result.x are not the same sign
			Result.x = 0.0f;
	}

	// Clamp to TopSpeed
	if (Result.x > 0.0f)
	{
		Result.x = Clamp(Result.x, 0.0f, TopSpeed);
	}
	else
	{
		Result.x = Clamp(Result.x, -TopSpeed, 0.0f);
	}

	return Result;
}

void MovementModeBase::Activate()
{
	bIsActive = true;
}

void MovementModeBase::Deactivate()
{
	bIsActive = false;
}

bool MovementModeBase::IsActive() const
{
	return bIsActive;
}

float MovementModeBase::GetTopSpeed() const
{
	return TopSpeed;
}
