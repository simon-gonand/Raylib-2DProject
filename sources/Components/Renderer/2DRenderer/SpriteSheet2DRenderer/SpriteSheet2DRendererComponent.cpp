#include "SpriteSheet2DRendererComponent.h"
#include <raymath.h>

SpriteSheet2DRendererComponent::SpriteSheet2DRendererComponent(std::shared_ptr<Actor> Owner, const char* DefaultTexturePath) :
	Renderer2DComponent(Owner, DefaultTexturePath)
{
}

void SpriteSheet2DRendererComponent::Initialize()
{
	IdleAnimation = LoadTexture("assets/Characters/Player/SpriteSheets/_Idle.png");
}

void SpriteSheet2DRendererComponent::Update(float DeltaTime)
{
	Vector3 DrawLocation = GetOwnerLocation();
	Vector3 Scale = GetOwnerScale();

	if (IdleAnimation.width > 0.0f, IdleAnimation.height > 0.0f) 
	{
		Rectangle Source = {
			0,
			0,
			IdleAnimation.width / 10,
			IdleAnimation.height
		};

		Rectangle Destination = {
			DrawLocation.x,
			DrawLocation.y,
			Scale.x,
			Scale.y
		};
		DrawTexturePro(IdleAnimation, Source, Destination, {Scale.x/2, Scale.y/2}, 0.0f, WHITE);
	}
	else 
	{
		Renderer2DComponent::Update(DeltaTime);
	}
}
