#include "Trigger.h"

Trigger::Trigger(std::shared_ptr<PhysicsComponent> InPhysicsComp):
	Actor(), PhysicsComp{InPhysicsComp}
{
}

void Trigger::Initialize()
{
	AddComponent(PhysicsComp);
}
