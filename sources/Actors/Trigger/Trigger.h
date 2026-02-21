#pragma once

#include "../BaseClass/Actor.h"
#include "../../Components/Physics/PhysicsComponent.h"

class Trigger : public Actor
{
public:
	Trigger(std::shared_ptr<PhysicsComponent> InPhysicsComp);

protected:
	virtual void Initialize() override;

	std::shared_ptr<PhysicsComponent> PhysicsComp;
};