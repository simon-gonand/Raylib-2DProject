#include "TransformComponent.h"

TransformComponent::TransformComponent(std::shared_ptr<Actor> InOwner, const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale):
	ComponentBase(InOwner)
{
	RelativeTransform.translation = InLocation;
	RelativeTransform.rotation = InRotation;
	RelativeTransform.scale = InScale;
}

const Vector3& TransformComponent::GetComponentLocation() const
{
	return RelativeTransform.translation;
}

const Quaternion& TransformComponent::GetComponentRotation() const
{
	return RelativeTransform.rotation;
}

const Vector3& TransformComponent::GetComponentScale() const
{
	return RelativeTransform.scale;
}

const Vector3& TransformComponent::GetWorldLocation() const
{
	return Vector3Add(GetOwnerLocation(), RelativeTransform.translation);
}

const Quaternion& TransformComponent::GetWorldRotation() const
{
	return QuaternionAdd(GetOwnerRotation(), RelativeTransform.rotation);
}

const Vector3& TransformComponent::GetWorldScale() const
{
	return Vector3Multiply(GetOwnerScale(), RelativeTransform.scale);
}
