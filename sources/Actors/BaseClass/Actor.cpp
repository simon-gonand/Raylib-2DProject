#include "Actor.h"

#include <raymath.h>

#include "../../Components/BaseClass/ComponentBase.h"
#include <iostream>

Actor::Actor()
{
}

void Actor::Initialize()
{
}

void Actor::AddComponent(std::shared_ptr<ComponentBase> Component)
{
	Components.push_back(Component);
	Component->Initialize();
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

void Actor::SetActorLocation(const Vector3& NewLocation, bool bTriggerEvent)
{
	ActorTransform.translation = NewLocation;
	if (bTriggerEvent)
	{
		for (DelegateBase<void, const Vector3&>* Delegate : OnLocationSet)
		{
			Delegate->Invoke(NewLocation);
		}
	}
}

void Actor::AddActorLocation(const Vector3& AddedLocation, bool bTriggerEvent)
{
	ActorTransform.translation = Vector3Add(ActorTransform.translation, AddedLocation);
	if (bTriggerEvent)
	{
		for (DelegateBase<void, const Vector3&>* Delegate : OnLocationSet)
		{
			Delegate->Invoke(ActorTransform.translation);
		}
	}
}

void Actor::SetActorRotation(const Quaternion& NewRotation, bool bTriggerEvent)
{
	ActorTransform.rotation = NewRotation;
	if (bTriggerEvent)
	{
		for (DelegateBase<void, const Quaternion&>* Delegate : OnRotationSet)
		{
			Delegate->Invoke(NewRotation);
		}
	}
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