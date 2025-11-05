#include "Renderer2DComponent.h"
#include "../../../Helpers/Globals/Globals.h"

Renderer2DComponent::Renderer2DComponent(std::shared_ptr<Actor> Owner, const char* TexturePath, const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale, const Vector2& InSize)
	:RendererComponent(Owner, InLocation, InRotation, InScale)
{
	DefaultTexturePath = TexturePath;
	Size = InSize;
}

void Renderer2DComponent::Initialize()
{
	if (DefaultTexturePath && DefaultTexturePath[0])
		DefaultTexture2D = LoadTexture(DefaultTexturePath);
}

void Renderer2DComponent::Update(float DeltaTime)
{
	Vector3 DrawLocation = GetWorldLocation();
	Quaternion DrawRotation = GetWorldRotation();
	Vector2 ScaleSize = GetSizeScaledWithRatio();
	if (DefaultTexture2D.width > 0.0f && DefaultTexture2D.height > 0.0f)
	{
		DrawTextureEx(DefaultTexture2D, { DrawLocation.x, DrawLocation.y }, DrawRotation.x, 1.0f, WHITE);
	}
	else 
	{
		// If no texture just draw a debug rectangle
	
		Rectangle rect = {
			DrawLocation.x,
			DrawLocation.y,
			ScaleSize.x,
			ScaleSize.y
		};

		DrawRectanglePro(rect, { ScaleSize.x / 2, ScaleSize.y / 2 }, DrawRotation.x, WHITE);
	}
}

Vector2 Renderer2DComponent::GetSizeScaledWithRatio() const
{
	Vector3 Scale = GetWorldScale();
	Scale = { Scale.x * 2 * PTM_RATIO, Scale.y * 2 * PTM_RATIO, 0.0f };
	return { Size.x * Scale.x, Size.y * Scale.y };
}
