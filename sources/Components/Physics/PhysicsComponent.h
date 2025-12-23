#pragma once

#include"../BaseClass/TransformComponent.h"

class PhysicsComponent: public TransformComponent
{
public:
	virtual Vector3 GetWorldPhysicsLocation() const = 0;
	virtual Vector3 GetLinearVelocity() const = 0;

	virtual void SetLinearVelocity(const Vector3& NewVelocity) = 0;
	virtual void AddLinearVelocity(const Vector3& NewVelocity) = 0;

	virtual void ApplyForce(const Vector3& Force) = 0;

	virtual void SetFriction(float NewFriction) = 0;

protected:
	PhysicsComponent(std::shared_ptr<Actor> InOwner, bool bAutoActivate = true, const Vector3& InLocation = { 0.0f }, const Quaternion& InRotation = { 0.0f }, const Vector3& InScale = { 1.0f, 1.0f, 1.0f });
};

