#include "SlidingMovementMode.h"

#include <iostream>

SlidingMovementMode::SlidingMovementMode(float InAcceleration, float InDeceleration, float InTopSpeed, std::shared_ptr<MovementComponent> InMovementComp, float InMinimalVelocityToTrigger, float InFallingAcceleration, float InMaxFallingSpeed)
	: MovementModeBase(InAcceleration, InDeceleration, InTopSpeed), MovementComp{InMovementComp}, InitialVelocity{ 0.0f }, MinimalVelocityToTrigger{InMinimalVelocityToTrigger}, FallingAcceleration{InFallingAcceleration}, MaxFallingSpeed{InMaxFallingSpeed}
{
}

bool SlidingMovementMode::CanSwitchToMode(EMovementMode CurrentMovementMode, const Vector3& CurrentVelocity) const
{
	return CurrentMovementMode != EMovementMode::THROWN && CurrentMovementMode != EMovementMode::GRAPPLING_THROWN && abs(CurrentVelocity.x) > MinimalVelocityToTrigger &&
		MovementModeBase::CanSwitchToMode(CurrentMovementMode, CurrentVelocity);
}

void SlidingMovementMode::OnSwitch()
{
	InitialVelocity = 0.0f;
}

Vector3 SlidingMovementMode::PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity)
{
	Vector3 Result = CurrentVelocity;

	if ((MovementComp->GetPreviousMovementMode() == EMovementMode::FALLING || MovementComp->GetPreviousMovementMode() == EMovementMode::JUMPING) && !FloatEquals(CurrentVelocity.y, 0.0f))
	{
		Result.y += FallingAcceleration * DeltaTime;
		Result.y = Clamp(Result.y, 0.0f, MaxFallingSpeed);
	}

	if (InitialVelocity == 0.0f) 
	{
		InitialVelocity = CurrentVelocity.x;
	}
	if (FloatEquals(CurrentVelocity.y, 0.0f))
	{
		Result.x += (Result.x > 0.0f ? -Deceleration : Deceleration) * DeltaTime;

		if (CurrentVelocity.x * Result.x < 0.0f) // Set Velocity to 0 if CurrentVelocity.x & Result.x are not the same sign
			Result.x = 0.0f;
	}

	if (Result.x == 0.0f)
		MovementComp->SwitchMovementMode(EMovementMode::GROUND);

	return Result;
}
