#include "JumpingMovementMode.h"

JumpingMovementMode::JumpingMovementMode(float InAcceleration, float InDeceleration, float InTopSpeed, float InJumpSpeed, std::shared_ptr<MovementComponent> InMovementComponent)
	: MovementModeBase(InAcceleration, InDeceleration, InTopSpeed), JumpSpeed{ InJumpSpeed }, MovementComp {InMovementComponent}
{
}

bool JumpingMovementMode::CanSwitchToMode(EMovementMode CurrentMovementMode) const
{
	return CurrentMovementMode != EMovementMode::FALLING;
}

Vector3 JumpingMovementMode::PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity)
{
	Vector3 Result = MovementModeBase::PerformMovement(DeltaTime, Input, CurrentVelocity);

	if(FloatEquals(Result.y, 0.0f))
		Result = Vector3Add(Result, { 0.0f, JumpSpeed });

	if(Result.y > 0.0f)
 		MovementComp->SwitchMovementMode(EMovementMode::FALLING);

	return Result;
}
