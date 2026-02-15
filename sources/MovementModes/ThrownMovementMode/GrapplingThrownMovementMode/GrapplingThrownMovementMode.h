#pragma once

#include "../ThrownMovementMode.h"

class GrapplingThrownMovementMode : public ThrownMovementMode
{
public:
	GrapplingThrownMovementMode(std::shared_ptr<PhysicsComponent> OwnerPhysicsComponent, std::shared_ptr<MovementComponent> OwnerMovementComp, const float& InAcceleration = 1.0f, const float& InTopSpeed = 20.0f, const float& InEndDistance = 20.0f, const float& InVelocityLerpSpeed = 1.0f);

	void SetFinalLocation(const Vector3& InFinalLocation);

protected:
	virtual void OnSwitch() override;
	virtual Vector3 PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity) override;

private:
	Vector3 FinalLocation = Vector3Zero();
	float EndDistance = 20.0f;

	float TopSpeed;
	float Acceleration;
	float TargetSpeed;

	float VelocityLerpSpeed;
	float VelocityLerpAlpha;
};

