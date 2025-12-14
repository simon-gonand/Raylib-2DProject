#include "SlidingMovementMode.h"

SlidingMovementMode::SlidingMovementMode(float InAcceleration, float InDeceleration, float InTopSpeed, std::shared_ptr<MovementComponent> InMovementComp)
	: MovementModeBase(InAcceleration, InDeceleration, InTopSpeed), MovementComp {InMovementComp}, InitialVelocity{ 0.0f }
{
}

bool SlidingMovementMode::CanSwitchToMode(EMovementMode CurrentMovementMode, const Vector3& CurrentVelocity) const
{
	return CurrentMovementMode != EMovementMode::JUMPING && CurrentMovementMode != EMovementMode::FALLING && CurrentVelocity.x > 9.0f;
}

void SlidingMovementMode::OnSwitch()
{
	InitialVelocity = 0.0f;
	DeaccelerateAlpha = 0.0f;
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
