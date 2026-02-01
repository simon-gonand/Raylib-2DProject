#pragma once

#include "../ThrownMovementMode.h"

class GrapplingThrownMovementMode : public ThrownMovementMode
{
public:
	GrapplingThrownMovementMode(std::shared_ptr<PhysicsComponent> OwnerPhysicsComponent, std::shared_ptr<MovementComponent> OwnerMovementComp);

	void SetFinalLocation(const Vector3& InFinalLocation);

protected:
	virtual void OnSwitch() override;
	virtual Vector3 PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity) override;

private:
	Vector3 FinalLocation =  Vector3Zero();
	float MinimalDistance = 20.0f;

	float Speed = 20.0f;
};

