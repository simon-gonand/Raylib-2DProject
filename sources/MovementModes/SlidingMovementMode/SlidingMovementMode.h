#pragma once

#include "../MovementModeBase.h"

class SlidingMovementMode : public MovementModeBase
{
public:
	SlidingMovementMode(float InAcceleration, float InDeceleration, float InTopSpeed, std::shared_ptr<MovementComponent> InMovementComp);

protected:
	virtual bool CanSwitchToMode(EMovementMode CurrentMovementMode, const Vector3& CurrentVelocity) const override;
	virtual void OnSwitch() override;
	virtual Vector3 PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity) override;

private:
	float InitialVelocity;

	std::shared_ptr<MovementComponent> MovementComp;
};