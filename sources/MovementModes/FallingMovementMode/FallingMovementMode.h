#pragma once

#include "../MovementModeBase.h"

class FallingMovementMode : public MovementModeBase
{
public:
	FallingMovementMode(float InAcceleration, float InDeceleration, float InTopSpeed, float InJumpSpeedDeceleration, float InReduceJumpSpeedTargetScale);

protected:
	virtual void OnSwitch();
	virtual bool CanSwitchToMode(EMovementMode CurrentMovementMode, const Vector3& CurrentVelocity) const;
	virtual Vector3 PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity) override;

private:
	bool bFirstPerformMovement;

	float ReduceJumpSpeedTargetScale;
	float JumpSpeedDeceleration;
	float InitialJumpSpeed;
	float CurrentJumpSpeedLerpAlpha;
};