#pragma once

#include "ComponentBase.h"

#include <raymath.h>

class TransformComponent : public ComponentBase
{
public:
	TransformComponent(std::shared_ptr<Actor> InOwner, bool bAutoActivate = true, const Vector3& InLocation = {0.0f}, const Quaternion& InRotation = {0.0f}, const Vector3& InScale = {1.0f, 1.0f, 1.0f});

	void SetComponentLocation(const Vector3& NewLocation);
	void SetComponentRotation(const Quaternion& NewRotation);
	void SetComponentScale(const Vector3& NewScale);

	const Vector3& GetComponentLocation() const;
	const Quaternion& GetComponentRotation() const;
	const Vector3& GetComponentScale() const;

	const Vector3& GetWorldLocation() const;
	const Quaternion& GetWorldRotation() const;
	const Vector3& GetWorldScale() const;

private:
	Transform RelativeTransform;
};