#pragma once

#include "../BaseClass/TransformComponent.h"

class RendererComponent : public TransformComponent 
{
protected:
	RendererComponent(std::shared_ptr<Actor> Owner, const Vector3& InLocation = { 0.0f }, const Quaternion& InRotation = { 0.0f }, const Vector3& InScale = { 1.0f, 1.0f, 1.0f });
};