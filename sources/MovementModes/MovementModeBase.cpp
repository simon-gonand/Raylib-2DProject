#include "MovementModeBase.h"

#include <iostream>
#include <raymath.h>

Vector3 MovementModeBase::LastVelocityIncrease = Vector3Zero();

MovementModeBase::MovementModeBase(float InAcceleration, float InDeceleration, float InTopSpeed):
	Acceleration{InAcceleration}, Deceleration{InDeceleration}, TopSpeed{InTopSpeed}, DeaccelerateAlpha{0.0f}
{
}

bool MovementModeBase::CanSwitchToMode(EMovementMode CurrentMovementMode) const
{
	return true;
}

Vector3 MovementModeBase::PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity)
{
	float Magnitude = Vector2Length(Input);
	Vector3 Result = CurrentVelocity;
	if (Magnitude > 0.0f)
	{
		Result.x += Input.x > 0.0f ? Acceleration : -Acceleration;
		DeaccelerateAlpha = 0.0f;
		LastVelocityIncrease = CurrentVelocity;
	}
	else if (!FloatEquals(Result.x, 0.0f))
	{
		DeaccelerateAlpha += DeltaTime * Deceleration;
		DeaccelerateAlpha = Clamp(DeaccelerateAlpha, 0.0f, 1.0f);
		Result.x = Lerp(LastVelocityIncrease.x, 0.0f, DeaccelerateAlpha);
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

	std::cout << CurrentVelocity.x << "; " << CurrentVelocity.y << std::endl;
	return Result;
}
