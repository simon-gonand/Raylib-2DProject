#pragma once

#include "../Trigger.h"

class ObstacleTrigger : public Trigger
{
public:
	ObstacleTrigger(std::shared_ptr<PhysicsComponent> InPhysicsComp);

protected:
	virtual void Initialize() override;

private:
	void OnBeginOverlap(PhysicsComponent* OtherComp);
};