#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(std::shared_ptr<Actor> InOwner, bool bAutoActivate, const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale) :
	TransformComponent(InOwner, bAutoActivate, InLocation, InRotation, InScale)
{
}

void PhysicsComponent::BroadcastOnBeginOverlap(PhysicsComponent* InVisitor) const
{
	for (DelegateBase<void, PhysicsComponent*>* Delegate : OnBeginOverlap)
	{
		Delegate->Invoke(InVisitor);
	}
}

void PhysicsComponent::BroadcastOnEndOverlap(PhysicsComponent* InVisitor) const
{
	for (DelegateBase<void, PhysicsComponent*>* Delegate : OnEndOverlap)
	{
		Delegate->Invoke(InVisitor);
	}
}
