#pragma once

#include "../../Components/Camera/CameraComponent.h"

class PlayerCameraComponent : public CameraComponent 
{
public:
	PlayerCameraComponent(std::shared_ptr<Actor> InOwner,
		const Vector2& InitialPos = { 0.0f }, const Vector2& Offset = { 0.0f }, const float& Rotation = 0.0f, const float& Zoom = 1.0f);
protected:
	virtual void Update(float Tick) override;
};