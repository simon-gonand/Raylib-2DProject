#include "ComponentBase.h"



ComponentBase::ComponentBase(std::shared_ptr<Actor> InOwner)
{
	Owner = InOwner;
}

std::shared_ptr<Actor> ComponentBase::GetOwner() const
{
	return Owner;
}

void ComponentBase::SetOwner(std::shared_ptr<Actor> NewOwner)
{
	Owner = NewOwner;
}
