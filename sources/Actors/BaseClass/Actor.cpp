#include "Actor.h"

#include "../../Components/BaseClass/ComponentBase.h"

void Actor::AddComponent(std::shared_ptr<ComponentBase> Component)
{
	Components.push_back(Component);
}

void Actor::RemoveComponent(std::shared_ptr<ComponentBase> Component)
{
	Components.remove(Component);
}

const std::list<std::shared_ptr<ComponentBase>>& Actor::GetAllComponents() const
{
	return Components;
}

void Actor::Update(float Tick)
{
	for (std::shared_ptr<ComponentBase> Component : Components) 
	{
		if (Component)
			Component->Update(Tick);
	}
}
