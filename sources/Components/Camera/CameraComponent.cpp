#include "CameraComponent.h"

#include "../../Managers/Camera/CameraManager.h"

CameraComponent::CameraComponent(std::shared_ptr<Actor> InOwner, bool bAutoActivate,
	const Vector2& InitialPos, const Vector2& Offset, const float& Rotation, const float& Zoom):
	ComponentBase(InOwner, bAutoActivate)
{
	Camera = Camera2D();
	Camera.target = InitialPos;
	Camera.offset = Offset;
	Camera.rotation = Rotation;
	Camera.zoom = Zoom;
}

CameraComponent::~CameraComponent()
{
	CameraManager::Get()->UnregisterCameraComponent(shared_from_this());
}

void CameraComponent::SwithToThisCamera()
{
	CameraManager::Get()->UseCamera(shared_from_this());
}

const Camera2D& CameraComponent::GetCamera() const
{
	return Camera;
}

void CameraComponent::Initialize()
{
	CameraManager::Get()->RegisterCameraComponent(shared_from_this());
}