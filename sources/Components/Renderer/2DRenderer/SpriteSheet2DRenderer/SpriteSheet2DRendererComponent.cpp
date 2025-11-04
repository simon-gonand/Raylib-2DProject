#include "SpriteSheet2DRendererComponent.h"
#include <raymath.h>

SpriteSheet2DRendererComponent::SpriteSheet2DRendererComponent(std::shared_ptr<Actor> Owner, const char* DefaultTexturePath) :
	Renderer2DComponent(Owner, DefaultTexturePath)
{
}

void SpriteSheet2DRendererComponent::Initialize()
{
	Texture2D IdleAnimationTexture = LoadTexture("assets/Characters/Player/SpriteSheets/_Idle.png");
	if (IdleAnimationTexture.width > 0.0f, IdleAnimationTexture.height > 0.0f) 
	{
		IdleAnimation = new SpriteSheet2DAnimation(IdleAnimationTexture, 10, 1, 0.15f, true, 0, 9);
		IdleAnimation->StartAnimation();
	}
}

void SpriteSheet2DRendererComponent::Update(float DeltaTime)
{

	Vector3 DrawLocation = GetOwnerLocation();
	Vector3 Scale = GetOwnerScale();

	if (IdleAnimation)
	{
		IdleAnimation->Update(DeltaTime);
		Rectangle Source = IdleAnimation->GetAnimationSourceRect();

		Rectangle Destination = {
			DrawLocation.x,
			DrawLocation.y,
			Scale.x,
			Scale.y
		};
		DrawTexturePro(IdleAnimation->GetAnimationTexture(), Source, Destination, {Scale.x / 2, Scale.y / 2}, 0.0f, WHITE);
	}
	else 
	{
		Renderer2DComponent::Update(DeltaTime);
	}
}
