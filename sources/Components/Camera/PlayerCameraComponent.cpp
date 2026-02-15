#include "PlayerCameraComponent.h"

#include "../../Helpers/Math/Vectors/Vectors.h"

PlayerCameraComponent::PlayerCameraComponent(std::shared_ptr<Actor> InOwner, bool bAutoActivate, const Vector2& InitialPos, const Vector2& Offset, const float& Rotation, const float& Zoom, const Vector2& InCameraNoMovementBoxOffsetSize):
	CameraComponent(InOwner, bAutoActivate, InitialPos, Offset, Rotation, Zoom), CameraNoMovementBoxOffsetSize{InCameraNoMovementBoxOffsetSize}
{
}

void PlayerCameraComponent::Update(float DeltaTime)
{
	CameraComponent::Update(DeltaTime);

	if (std::shared_ptr<Actor> CurrentOwner = GetOwner()) 
	{
		Vector3 ActorLocation = CurrentOwner->GetActorLocation();
		float XDistance = ActorLocation.x - Camera.target.x;
		if (abs(XDistance) > CameraNoMovementBoxOffsetSize.x / 2)
		{
			Camera.target.x += XDistance > 0 ? XDistance - CameraNoMovementBoxOffsetSize.x / 2 : XDistance + CameraNoMovementBoxOffsetSize.x / 2;
		}
		float YDistance = ActorLocation.y - Camera.target.y;
		if (abs(YDistance) > CameraNoMovementBoxOffsetSize.y / 2)
		{
			Camera.target.y += YDistance > 0 ? YDistance - CameraNoMovementBoxOffsetSize.y / 2 : YDistance + CameraNoMovementBoxOffsetSize.y / 2;
		}
	}
}

void PlayerCameraComponent::DrawDebug(float DeltaTime)
{
	DrawRectangleLines(Camera.target.x - CameraNoMovementBoxOffsetSize.x / 2, Camera.target.y - CameraNoMovementBoxOffsetSize.y / 2, CameraNoMovementBoxOffsetSize.x, CameraNoMovementBoxOffsetSize.y, RED);
}
