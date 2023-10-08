#include "Actor.h"

#include "../../Components/BaseClass/ComponentBase.h"

Actor::Actor()
{
	Transform = new Transform2D();
}

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

Transform2D* Actor::GetActorTransform() const
{
	return Transform;
}

const MyVector2& Actor::GetActorLocation() const
{
	return Transform->GetLocation();
}

const float& Actor::GetActorRotation() const
{
	return Transform->GetRotation();
}

const MyVector2& Actor::GetActorScale() const
{
	return Transform->GetScale();
}

void Actor::SetActorLocation(const MyVector2& NewLocation)
{
	Transform->SetLocation(NewLocation);
}

void Actor::AddActorLocation(const MyVector2& AddedLocation)
{
	Transform->AddLocation(AddedLocation);
}

void Actor::SetActorRotation(const float& NewRotation)
{
	Transform->SetRotation(NewRotation);
}

void Actor::SetActorScale(const MyVector2& NewScale)
{
	Transform->SetScale(NewScale);
}

void Actor::Update(float Tick)
{
	for (std::shared_ptr<ComponentBase> Component : Components) 
	{
		if (Component)
			Component->Update(Tick);
	}
}
