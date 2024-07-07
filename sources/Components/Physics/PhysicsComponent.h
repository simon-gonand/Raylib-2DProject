#pragma once

#include"../BaseClass/ComponentBase.h"

class PhysicsComponent: public ComponentBase
{
public:
	virtual Vector2 GetWorldLocation() const = 0;
	virtual Vector2 GetLinearVelocity() const = 0;

	virtual void SetLinearVelocity(const Vector2& NewVelocity) = 0;
	virtual void AddLinearVelocity(const Vector2& NewVelocity) = 0;

protected:
	PhysicsComponent(std::shared_ptr<Actor> InOwner);
};

