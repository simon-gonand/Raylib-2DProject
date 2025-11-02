#include "RendererComponent.h"

#include <raymath.h>

RendererComponent::RendererComponent(std::shared_ptr<Actor> Owner) :
	ComponentBase(Owner)
{
}

Vector3 RendererComponent::GetOwnerLocation() const
{
	if (std::shared_ptr<Actor> ActorOwner = GetOwner())
	{
		return ActorOwner->GetActorLocation();
	}

	return Vector3Zero();
}

Quaternion RendererComponent::GetOwnerRotation() const
{
	if (std::shared_ptr<Actor> ActorOwner = GetOwner())
	{
		return ActorOwner->GetActorRotation();
	}

	return Quaternion();
}

Vector3 RendererComponent::GetOwnerScale() const
{
	if (std::shared_ptr<Actor> ActorOwner = GetOwner()) 
	{
		return ActorOwner->GetActorScale();
	}

	return Vector3Zero();
}