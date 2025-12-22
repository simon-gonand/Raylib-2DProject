#include "ComponentBase.h"

#include <raymath.h>

ComponentBase::ComponentBase(std::shared_ptr<Actor> InOwner, bool bAutoActivate)
	: Owner {InOwner}, bIsActive{bAutoActivate}
{
}

std::shared_ptr<Actor> ComponentBase::GetOwner() const
{
	return Owner;
}

void ComponentBase::SetOwner(std::shared_ptr<Actor> NewOwner)
{
	Owner = NewOwner;
}

void ComponentBase::Update(float DeltaTime)
{
	if (bDrawDebug)
		DrawDebug(DeltaTime);
}

void ComponentBase::Activate()
{
	bIsActive = true;
}

void ComponentBase::Deactivate()
{
	bIsActive = false;
}

bool ComponentBase::IsActive() const
{
	return bIsActive;
}

Vector3 ComponentBase::GetOwnerLocation() const
{
	if (std::shared_ptr<Actor> ActorOwner = GetOwner())
	{
		return ActorOwner->GetActorLocation();
	}

	return Vector3Zero();
}

Quaternion ComponentBase::GetOwnerRotation() const
{
	if (std::shared_ptr<Actor> ActorOwner = GetOwner())
	{
		return ActorOwner->GetActorRotation();
	}

	return Quaternion();
}

Vector3 ComponentBase::GetOwnerScale() const
{
	if (std::shared_ptr<Actor> ActorOwner = GetOwner())
	{
		return ActorOwner->GetActorScale();
	}

	return Vector3Zero();
}

void ComponentBase::SetDrawDebug(bool bInDrawDebug)
{
	bDrawDebug = bInDrawDebug;
}
