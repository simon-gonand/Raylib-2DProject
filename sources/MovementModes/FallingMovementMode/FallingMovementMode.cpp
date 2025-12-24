#include "FallingMovementMode.h"

FallingMovementMode::FallingMovementMode(float InAcceleration, float InDeceleration, float InTopSpeed, float InJumpSpeedDeceleration, float InReduceJumpSpeedTargetScale)
	: MovementModeBase(InAcceleration, InDeceleration, InTopSpeed), JumpSpeedDeceleration{ InJumpSpeedDeceleration }, ReduceJumpSpeedTargetScale{InReduceJumpSpeedTargetScale}, 
	CurrentJumpSpeedLerpAlpha{0.0f}, InitialJumpSpeed{0.0f}, bFirstPerformMovement {true}
{
}

void FallingMovementMode::OnSwitch()
{
	bFirstPerformMovement = true;
}

bool FallingMovementMode::CanSwitchToMode(EMovementMode CurrentMovementMode, const Vector3& CurrentVelocity) const
{
	return MovementModeBase::CanSwitchToMode(CurrentMovementMode, CurrentVelocity);
}

Vector3 FallingMovementMode::PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity)
{
	Vector3 Result = MovementModeBase::PerformMovement(DeltaTime, Input, CurrentVelocity);

	if (CurrentVelocity.y < 0.0f) 
	{
		if (bFirstPerformMovement) 
		{
			CurrentJumpSpeedLerpAlpha = 0.0f;
			ReduceJumpSpeedTargetScale = CurrentVelocity.y / 1.5f;
			InitialJumpSpeed = CurrentVelocity.y;
		}

		if (CurrentJumpSpeedLerpAlpha < 1.0f && ReduceJumpSpeedTargetScale > Result.y)
		{
			CurrentJumpSpeedLerpAlpha += DeltaTime * JumpSpeedDeceleration;
			CurrentJumpSpeedLerpAlpha = Clamp(CurrentJumpSpeedLerpAlpha, 0.0f, 1.0f);
			Result.y = Lerp(InitialJumpSpeed, ReduceJumpSpeedTargetScale, CurrentJumpSpeedLerpAlpha);
		}
	}

	bFirstPerformMovement = false;
	return Result;
}
