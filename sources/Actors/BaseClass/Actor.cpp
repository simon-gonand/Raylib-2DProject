#include "Actor.h"

#include <raymath.h>

#include "../../Components/BaseClass/ComponentBase.h"

Actor::Actor()
{
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

const Transform& Actor::GetActorTransform() const
{
	return ActorTransform;
}

const Vector3& Actor::GetActorLocation() const
{
	return ActorTransform.translation;
}

const Quaternion& Actor::GetActorRotation() const
{
	return ActorTransform.rotation;
}

const Vector3& Actor::GetActorScale() const
{
	return ActorTransform.scale;
}

void Actor::SetActorLocation(const Vector3& NewLocation)
{
	ActorTransform.translation = NewLocation;
}

void Actor::AddActorLocation(const Vector3& AddedLocation)
{
	ActorTransform.translation = Vector3Add(ActorTransform.translation, AddedLocation);
}

void Actor::SetActorRotation(const Quaternion& NewRotation)
{
	ActorTransform.rotation = NewRotation;
}

void Actor::SetActorScale(const Vector3& NewScale)
{
	ActorTransform.scale = NewScale;
}

void Actor::Update(float Tick)
{
	for (std::shared_ptr<ComponentBase> Component : Components) 
	{
		if (Component)
			Component->Update(Tick);
	}
}
