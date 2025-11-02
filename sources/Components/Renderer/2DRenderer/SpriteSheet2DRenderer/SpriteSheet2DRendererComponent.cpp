#include "SpriteSheet2DRendererComponent.h"

SpriteSheet2DRendererComponent::SpriteSheet2DRendererComponent(std::shared_ptr<Actor> Owner, const char* DefaultTexturePath) :
	Renderer2DComponent(Owner, DefaultTexturePath)
{
}

void SpriteSheet2DRendererComponent::Initialize()
{
	IdleAnimation = &LoadTexture("$(ProjectDir)/assets/Characters/Player/SpriteSheets/_Idle.png");
}

void SpriteSheet2DRendererComponent::Update(float DeltaTime)
{
	Vector3 DrawLocation = GetOwnerLocation();
	Vector3 Scale = GetOwnerScale();

	// Draw centered to correspond to physics
	DrawRectangleGradientEx(
		{ DrawLocation.x - Scale.x / 2,
		DrawLocation.y - Scale.y / 2,
		Scale.x,
		Scale.y },
		RED, BLUE, WHITE, GREEN
	);
}
