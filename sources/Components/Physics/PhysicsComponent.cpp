#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(std::shared_ptr<Actor> InOwner, bool bAutoActivate, const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale) :
	TransformComponent(InOwner, bAutoActivate, InLocation, InRotation, InScale)
{
}
