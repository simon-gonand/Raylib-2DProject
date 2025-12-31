#include "TransformComponent.h"

TransformComponent::TransformComponent(std::shared_ptr<Actor> InOwner, bool bAutoActivate, const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale):
	ComponentBase(InOwner, bAutoActivate)
{
	RelativeTransform.translation = InLocation;
	RelativeTransform.rotation = InRotation;
	RelativeTransform.scale = InScale;
}

void TransformComponent::SetComponentLocation(const Vector3& NewLocation)
{
	RelativeTransform.translation = NewLocation;
}

void TransformComponent::SetComponentRotation(const Quaternion& NewRotation)
{
	RelativeTransform.rotation = NewRotation;
}

void TransformComponent::SetComponentScale(const Vector3& NewScale)
{
	RelativeTransform.scale = NewScale;
}

void TransformComponent::SetWorldLocation(const Vector3& NewLocation)
{
	RelativeTransform.translation = Vector3Subtract(NewLocation, GetOwnerLocation());
}

void TransformComponent::SetWorldRotation(const Quaternion& NewRotation)
{
	RelativeTransform.rotation = QuaternionSubtract(NewRotation, GetOwnerRotation());
}

void TransformComponent::SetWorldScale(const Vector3& NewScale)
{
	Vector3Divide(NewScale, GetOwnerScale());
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
