#pragma once

#include "../MovementModeBase.h"

class SlidingMovementMode : public MovementModeBase
{
public:
	SlidingMovementMode(float InAcceleration, float InDeceleration, float InTopSpeed, std::shared_ptr<MovementComponent> InMovementComp, float InMinimalVelocityToTrigger, float InFallingAcceleration, float InMaxFallingSpeed);

protected:
	virtual bool CanSwitchToMode(EMovementMode CurrentMovementMode, const Vector3& CurrentVelocity) const override;
	virtual void OnSwitch() override;
	virtual Vector3 PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity) override;

private:
	float InitialVelocity;
	float MinimalVelocityToTrigger;
	float FallingAcceleration;
	float MaxFallingSpeed;

	std::shared_ptr<MovementComponent> MovementComp;
};