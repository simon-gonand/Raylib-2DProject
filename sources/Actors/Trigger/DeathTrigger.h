#pragma once

#include "../BaseClass/Actor.h"
#include "../../Components/Physics/PhysicsComponent.h"

class DeathTrigger : public Actor
{
public:
	DeathTrigger(std::shared_ptr<PhysicsComponent> InPhysicsComp);

protected:
	virtual void Initialize() override;

private:
	std::shared_ptr<PhysicsComponent> PhysicsComp;

	void OnBeginOverlap(PhysicsComponent* OtherComp);
};