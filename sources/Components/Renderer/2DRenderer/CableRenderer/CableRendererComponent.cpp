#include "CableRendererComponent.h"
#include "../../../../Helpers/Math/Vectors/Vectors.h"

CableRendererComponent::CableRendererComponent(std::shared_ptr<Actor> InOwner, const char* TexturePath, bool bInUseComponentLocationAsStartPosition, 
	bool bAutoActivate, const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale, const Vector2& InSize, std::shared_ptr<AnimationManager> InAnimManager)
	: Renderer2DComponent(InOwner, TexturePath, bAutoActivate, InLocation, InRotation, InScale, InSize, InAnimManager), 
	bUseComponentLocationAsStartPosition{ bInUseComponentLocationAsStartPosition }, EndPosition {0.0f}
{
	if (!bInUseComponentLocationAsStartPosition)
		StartPosition = Vector2Zero();
}

void CableRendererComponent::SetStartPosition(const Vector2& InStartPosition)
{
	StartPosition = InStartPosition;
	bUseComponentLocationAsStartPosition = Vector2Equals(StartPosition, Vector::Vector3ToVector2(GetWorldLocation()));
}

void CableRendererComponent::SetEndPosition(const Vector2& InEndPosition)
{
	EndPosition = InEndPosition;
}

void CableRendererComponent::Update(float DeltaTime)
{
	if (bUseComponentLocationAsStartPosition) 
	{
		StartPosition = Vector::Vector3ToVector2(GetWorldLocation());
	}

	if(DefaultTexture2D.height <= 0.0f || DefaultTexture2D.width <= 0.0f)
		DrawLineEx(StartPosition, EndPosition, 1.5f, WHITE);
}
