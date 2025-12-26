#include "JumpingMovementMode.h"

JumpingMovementMode::JumpingMovementMode(float InAcceleration, float InDeceleration, float InTopSpeed, float InJumpSpeed, int InMaxJumpCount,
	std::shared_ptr<MovementComponent> InMovementComponent)
	: MovementModeBase(InAcceleration, InDeceleration, InTopSpeed), JumpSpeed{ InJumpSpeed }, MaxJumpCount{InMaxJumpCount}, MovementComp {InMovementComponent}
{
}

void JumpingMovementMode::IncrementJumpCount()
{
	++JumpCount;
}

void JumpingMovementMode::ResetJumpCount()
{
	JumpCount = 0;
	PreviousFrameJumpCount = 0;
}

void JumpingMovementMode::OnSwitch()
{
	if (JumpCount == 0 && MovementComp->GetPreviousMovementMode() == EMovementMode::FALLING)
		++JumpCount;
}

bool JumpingMovementMode::CanSwitchToMode(EMovementMode CurrentMovementMode, const Vector3& CurrentVelocity) const
{
	return JumpCount < MaxJumpCount && CurrentMovementMode != EMovementMode::THROWN && CurrentMovementMode != EMovementMode::GRAPPLING_THROWN &&
		MovementModeBase::CanSwitchToMode(CurrentMovementMode, CurrentVelocity);
}

Vector3 JumpingMovementMode::PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity)
{
	Vector3 Result = MovementModeBase::PerformMovement(DeltaTime, Input, CurrentVelocity);

	if(PreviousFrameJumpCount < JumpCount)
		Result = Vector3Add(Result, { 0.0f, JumpSpeed });

	PreviousFrameJumpCount = JumpCount;

	if(Result.y > 0.0f)
 		MovementComp->SwitchMovementMode(EMovementMode::FALLING);

	return Result;
}
