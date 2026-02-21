#pragma once

#include "../Trigger.h"

class DeathTrigger : public Trigger
{
public:
	DeathTrigger(std::shared_ptr<PhysicsComponent> InPhysicsComp);

protected:
	virtual void Initialize() override;

private:
	void OnBeginOverlap(PhysicsComponent* OtherComp);
};