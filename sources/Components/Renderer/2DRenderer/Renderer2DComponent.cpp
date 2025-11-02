#include "Renderer2DComponent.h"

Renderer2DComponent::Renderer2DComponent(std::shared_ptr<Actor> Owner, const char* TexturePath)
	:RendererComponent(Owner)
{
	DefaultTexturePath = TexturePath;
}

void Renderer2DComponent::Initialize()
{
	if (DefaultTexturePath && DefaultTexturePath[0])
		DefaultTexture2D = LoadTexture(DefaultTexturePath);
}

void Renderer2DComponent::Update(float DeltaTime)
{
	Vector3 DrawLocation = GetOwnerLocation();
	Vector3 Scale = GetOwnerScale();
	if (DefaultTexture2D.width > 0.0f && DefaultTexture2D.height > 0.0f)
	{
		DrawTexture(DefaultTexture2D, DrawLocation.x, DrawLocation.y, Color({ 0 }));
	}
	else 
	{
		// If no texture just draw a debug rectangle
	
		Rectangle rect = {
			DrawLocation.x,
			DrawLocation.y,
			Scale.x,
			Scale.y
		};

		DrawRectanglePro(rect, { Scale.x / 2, Scale.y / 2 }, 0.0f, WHITE);
	}
}
