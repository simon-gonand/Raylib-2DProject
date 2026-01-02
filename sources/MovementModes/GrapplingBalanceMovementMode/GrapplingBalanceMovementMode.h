#pragma once
#include "../MovementModeBase.h"
class GrapplingBalanceMovementMode : public MovementModeBase
{ 
public:
	GrapplingBalanceMovementMode(float InAcceleration, float InDeceleration, float InTopSpeed, std::shared_ptr<PhysicsComponent> InPhysicsComp, float InOverrideLinearDamping = 0.5f);

protected:
	virtual void OnSwitch() override;
	virtual bool CanSwitchToMode(EMovementMode PreviousMovementMode, const Vector3& CurrentVelocity) const override;
	virtual Vector3 PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity) override;
	virtual void OnEndMovement() override;

private:
	std::shared_ptr<PhysicsComponent> PhysicsComp;
	float OverrideLinearDamping;
	float BaseLinearDamping = 0.0f;
};

