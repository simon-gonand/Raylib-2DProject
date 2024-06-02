#pragma once

#include"../BaseClass/ComponentBase.h"

class PhysicsComponent: public ComponentBase
{
public:
	virtual Vector2 GetWorldLocation() const = 0;

protected:
	PhysicsComponent(std::shared_ptr<Actor> InOwner);
};

