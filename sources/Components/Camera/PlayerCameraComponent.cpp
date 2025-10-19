#include "PlayerCameraComponent.h"

#include "../../Helpers/Math/Vectors/Vectors.h"

PlayerCameraComponent::PlayerCameraComponent(std::shared_ptr<Actor> InOwner, const Vector2& InitialPos, const Vector2& Offset, const float& Rotation, const float& Zoom):
	CameraComponent(InOwner, InitialPos, Offset, Rotation, Zoom)
{
}

void PlayerCameraComponent::Update(float Tick)
{
	if (std::shared_ptr<Actor> CurrentOwner = GetOwner()) 
	{
		Vector3 ActorLocation = CurrentOwner->GetActorLocation();
		Camera.target = Vector2({ ActorLocation.x, -ActorLocation.y });
	}
}
