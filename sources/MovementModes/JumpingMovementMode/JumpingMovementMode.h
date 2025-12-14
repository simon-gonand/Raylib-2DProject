#pragma once

#include "../MovementModeBase.h"

class JumpingMovementMode : public MovementModeBase
{
public:
	JumpingMovementMode(float InAcceleration, float InDeceleration, float InTopSpeed, float InJumpSpeed, std::shared_ptr<MovementComponent> InMovementComponent);

protected:
	virtual bool CanSwitchToMode(EMovementMode CurrentMovementMode) const override;
	virtual Vector3 PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity) override;

private:
	float JumpSpeed;

	std::shared_ptr<MovementComponent> MovementComp;
};