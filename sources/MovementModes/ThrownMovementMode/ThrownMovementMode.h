#pragma once

#include "../MovementModeBase.h"

class ThrownMovementMode : public MovementModeBase
{
public:
	ThrownMovementMode(std::shared_ptr<PhysicsComponent> OwnerPhysicsComponent, std::shared_ptr<MovementComponent> OwnerMovementComp);

protected:
	virtual void OnSwitch();
	virtual Vector3 PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity) override;

private:
	std::shared_ptr<PhysicsComponent> PhysicsComp;
	std::shared_ptr<MovementComponent> MovementComp;
};

