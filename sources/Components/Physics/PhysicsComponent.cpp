#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(std::shared_ptr<Actor> InOwner, const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale) :
	TransformComponent(InOwner, InLocation, InRotation, InScale)
{
}
