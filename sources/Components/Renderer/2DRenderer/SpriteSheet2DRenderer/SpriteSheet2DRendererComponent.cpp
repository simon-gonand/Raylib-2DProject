#include "SpriteSheet2DRendererComponent.h"
#include <raymath.h>

SpriteSheet2DRendererComponent::SpriteSheet2DRendererComponent(std::shared_ptr<Actor> Owner, const char* DefaultTexturePath, const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale, const Vector2& InSize) :
	Renderer2DComponent(Owner, DefaultTexturePath, InLocation, InRotation, InScale, InSize)
{
}

void SpriteSheet2DRendererComponent::Initialize()
{
	Texture2D IdleAnimationTexture = LoadTexture("assets/Characters/Player/SpriteSheets/_Idle.png");
	if (IdleAnimationTexture.width > 0.0f && IdleAnimationTexture.height > 0.0f) 
	{
		IdleAnimation = new SpriteSheet2DAnimation(IdleAnimationTexture, 10, 1, 0.15f, true, 0, 9);
		IdleAnimation->StartAnimation();
	}
}

void SpriteSheet2DRendererComponent::Update(float DeltaTime)
{

	Vector3 DrawLocation = GetWorldLocation();
	Quaternion DrawRotation = GetWorldRotation();
	Vector2 SizeScaled = GetSizeScaledWithRatio();


	if (IdleAnimation)
	{
		IdleAnimation->Update(DeltaTime);
		Rectangle Source = IdleAnimation->GetAnimationSourceRect();

		Rectangle Destination = {
			DrawLocation.x,
			DrawLocation.y,
			SizeScaled.x,
			SizeScaled.y
		};

		DrawTexturePro(IdleAnimation->GetAnimationTexture(), Source, Destination, { SizeScaled.x / 2, SizeScaled.y / 2 }, DrawRotation.y, WHITE);
	}
	else 
	{
		Renderer2DComponent::Update(DeltaTime);
	}
}
