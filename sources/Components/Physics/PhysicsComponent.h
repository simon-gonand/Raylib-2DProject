#pragma once

#include"../BaseClass/TransformComponent.h"

class PhysicsComponent: public TransformComponent
{
public:
	virtual Vector2 GetWorldPhysicsLocation() const = 0;
	virtual Vector2 GetLinearVelocity() const = 0;

	virtual void SetLinearVelocity(const Vector2& NewVelocity) = 0;
	virtual void AddLinearVelocity(const Vector2& NewVelocity) = 0;

protected:
	PhysicsComponent(std::shared_ptr<Actor> InOwner, const Vector3& InLocation = { 0.0f }, const Quaternion& InRotation = { 0.0f }, const Vector3& InScale = { 1.0f, 1.0f, 1.0f });
};

