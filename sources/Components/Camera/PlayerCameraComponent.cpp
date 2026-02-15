#include "PlayerCameraComponent.h"

#include "../../Helpers/Math/Vectors/Vectors.h"

#include <raymath.h>

PlayerCameraComponent::PlayerCameraComponent(std::shared_ptr<Actor> InOwner, bool bAutoActivate, const Vector2& InitialPos, const Vector2& Offset, const float& Rotation, const float& Zoom, const Vector2& InCameraNoMovementBoxOffsetSize, const float& InCameraSpeed):
	CameraComponent(InOwner, bAutoActivate, InitialPos, Offset, Rotation, Zoom), CameraNoMovementBoxOffsetSize{InCameraNoMovementBoxOffsetSize}, CameraSpeed{InCameraSpeed}
{
}

void PlayerCameraComponent::Update(float DeltaTime)
{
	CameraComponent::Update(DeltaTime);

	if (std::shared_ptr<Actor> CurrentOwner = GetOwner()) 
	{
		Vector2 Target = Camera.target;
		Vector3 ActorLocation = CurrentOwner->GetActorLocation();
		float XDistance = ActorLocation.x - Camera.target.x;
		if (abs(XDistance) > CameraNoMovementBoxOffsetSize.x / 2)
		{
			Target.x += XDistance > 0 ? XDistance - CameraNoMovementBoxOffsetSize.x / 2 : XDistance + CameraNoMovementBoxOffsetSize.x / 2;
		}
		float YDistance = ActorLocation.y - Camera.target.y;
		if (abs(YDistance) > CameraNoMovementBoxOffsetSize.y / 2)
		{
			Target.y += YDistance > 0 ? YDistance - CameraNoMovementBoxOffsetSize.y / 2 : YDistance + CameraNoMovementBoxOffsetSize.y / 2;
		}

		Camera.target = Vector::Vector2InterpTo(Camera.target, Target, DeltaTime, CameraSpeed);
	}
}

void PlayerCameraComponent::DrawDebug(float DeltaTime)
{
	DrawRectangleLines(Camera.target.x - CameraNoMovementBoxOffsetSize.x / 2, Camera.target.y - CameraNoMovementBoxOffsetSize.y / 2, CameraNoMovementBoxOffsetSize.x, CameraNoMovementBoxOffsetSize.y, RED);
}
