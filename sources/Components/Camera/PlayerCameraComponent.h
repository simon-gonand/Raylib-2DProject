#pragma once

#include "../../Components/Camera/CameraComponent.h"

class PlayerCameraComponent : public CameraComponent 
{
public:
	PlayerCameraComponent(std::shared_ptr<Actor> InOwner, bool bAutoActivate = true,
		const Vector2& InitialPos = { 0.0f }, const Vector2& Offset = { 0.0f }, const float& Rotation = 0.0f, const float& Zoom = 1.0f, const Vector2& InCameraNoMovementBoxOffsetSize = {0.0f}, const float& InCameraSpeed = 10.0f);
protected:
	virtual void Update(float DeltaTime) override;
	virtual void DrawDebug(float DeltaTime) override;

private:
	Vector2 CameraNoMovementBoxOffsetSize;
	float CameraSpeed;
};