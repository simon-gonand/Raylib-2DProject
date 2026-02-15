#pragma once

#include "../MovementModeBase.h"

class JumpingMovementMode : public MovementModeBase
{
public:
	JumpingMovementMode(float InAcceleration, float InDeceleration, float InTopSpeed, float InJumpSpeed, int InMaxJumpCount,
		std::shared_ptr<MovementComponent> InMovementComponent);

	bool IncrementJumpCount();
	virtual void ResetJumpCount();
	int GetJumpCount();

protected:
	virtual void OnSwitch() override;
	virtual bool CanSwitchToMode(EMovementMode CurrentMovementMode, const Vector3& CurrentVelocity) const override;
	virtual Vector3 PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity) override;

private:
	float JumpSpeed;

	int JumpCount = 0;
	int PreviousFrameJumpCount = 0;
	int MaxJumpCount;

	std::shared_ptr<MovementComponent> MovementComp;
};