#include "RendererComponent.h"

#include <raymath.h>

RendererComponent::RendererComponent(std::shared_ptr<Actor> Owner, const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale) :
	TransformComponent(Owner, InLocation, InRotation, InScale)
{
}