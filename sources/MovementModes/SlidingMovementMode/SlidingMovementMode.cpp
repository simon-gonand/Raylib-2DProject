#include "SlidingMovementMode.h"

#include <iostream>

SlidingMovementMode::SlidingMovementMode(float InAcceleration, float InDeceleration, float InTopSpeed, std::shared_ptr<MovementComponent> InMovementComp, float InMinimalVelocityToTrigger)
	: MovementModeBase(InAcceleration, InDeceleration, InTopSpeed), MovementComp{InMovementComp}, InitialVelocity{ 0.0f }, MinimalVelocityToTrigger{InMinimalVelocityToTrigger}
{
}

bool SlidingMovementMode::CanSwitchToMode(EMovementMode CurrentMovementMode, const Vector3& CurrentVelocity) const
{
	return CurrentMovementMode != EMovementMode::JUMPING && CurrentMovementMode != EMovementMode::THROWN && CurrentMovementMode != EMovementMode::GRAPPLING_THROWN && abs(CurrentVelocity.x) > MinimalVelocityToTrigger &&
		MovementModeBase::CanSwitchToMode(CurrentMovementMode, CurrentVelocity);
}

void SlidingMovementMode::OnSwitch()
{
	InitialVelocity = 0.0f;
	DeaccelerateAlpha = 0.0f;
	std::cout << "SLIDING" << std::endl;
}

Vector3 SlidingMovementMode::PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity)
{
	Vector3 Result = Vector3Zero();

	if (InitialVelocity == 0.0f) 
	{
		InitialVelocity = CurrentVelocity.x;
	}
	DeaccelerateAlpha += DeltaTime * Deceleration;
	DeaccelerateAlpha = Clamp(DeaccelerateAlpha, 0.0f, 1.0f);
	Result.x = Lerp(InitialVelocity, 0.0f, DeaccelerateAlpha);

	if (Result.x == 0.0f)
		MovementComp->SwitchMovementMode(EMovementMode::GROUND);

	return Result;
}
