#pragma once

#include "../ThrownMovementMode.h"

class GrapplingThrownMovementMode : public ThrownMovementMode
{
public:
	GrapplingThrownMovementMode(std::shared_ptr<PhysicsComponent> OwnerPhysicsComponent, std::shared_ptr<MovementComponent> OwnerMovementComp);

protected:
	virtual void OnSwitch() override;
	virtual Vector3 PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity) override;
};

