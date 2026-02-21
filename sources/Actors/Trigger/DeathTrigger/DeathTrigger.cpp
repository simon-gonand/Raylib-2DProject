#include "DeathTrigger.h"

#include "../../Player/Player.h"

#include <memory>

DeathTrigger::DeathTrigger(std::shared_ptr<PhysicsComponent> InPhysicsComp):
	Trigger(InPhysicsComp)
{
}

void DeathTrigger::Initialize()
{
	Trigger::Initialize();
	PhysicsComp->BindOnBeginOverlap<DeathTrigger, &DeathTrigger::OnBeginOverlap>(this);
}

void DeathTrigger::OnBeginOverlap(PhysicsComponent* OtherComp)
{
	if (OtherComp && OtherComp->GetOwner())
	{
		if (std::shared_ptr<Player> P = std::dynamic_pointer_cast<Player>(OtherComp->GetOwner()))
		{
			P->Die(DeathReason::FALLING);
		}
	}
}