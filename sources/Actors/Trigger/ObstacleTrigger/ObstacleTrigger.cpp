#include "ObstacleTrigger.h"

#include "../../Player/Player.h"

ObstacleTrigger::ObstacleTrigger(std::shared_ptr<PhysicsComponent> InPhysicsComp):
	Trigger(InPhysicsComp)
{
}

void ObstacleTrigger::Initialize()
{
	Trigger::Initialize();
	PhysicsComp->BindOnBeginOverlap<ObstacleTrigger, &ObstacleTrigger::OnBeginOverlap>(this);
}

void ObstacleTrigger::OnBeginOverlap(PhysicsComponent* OtherComp)
{
	if (OtherComp && OtherComp->GetOwner())
	{
		if (std::shared_ptr<Player> P = std::dynamic_pointer_cast<Player>(OtherComp->GetOwner()))
		{
			P->Die(DeathReason::HIT);
		}
	}
}