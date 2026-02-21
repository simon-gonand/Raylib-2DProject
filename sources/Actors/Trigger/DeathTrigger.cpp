#include "DeathTrigger.h"

#include "../Player/Player.h"

#include <memory>

DeathTrigger::DeathTrigger(std::shared_ptr<PhysicsComponent> InPhysicsComp):
	Actor(), PhysicsComp{InPhysicsComp}
{
}

void DeathTrigger::Initialize()
{
	AddComponent(PhysicsComp);
	PhysicsComp->BindOnBeginOverlap<DeathTrigger, &DeathTrigger::OnBeginOverlap>(this);
}

void DeathTrigger::OnBeginOverlap(PhysicsComponent* OtherComp)
{
	if (OtherComp && OtherComp->GetOwner())
	{
		if (std::shared_ptr<Player> P = std::dynamic_pointer_cast<Player>(OtherComp->GetOwner()))
		{
			P->Respawn();
		}
	}
}