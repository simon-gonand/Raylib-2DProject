#include "SpriteSheet2DRendererComponent.h"
#include <raymath.h>

SpriteSheet2DRendererComponent::SpriteSheet2DRendererComponent(std::shared_ptr<Actor> Owner, const char* DefaultTexturePath, const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale, const Vector2& InSize, std::shared_ptr<AnimationManager> InAnimManager) :
	Renderer2DComponent(Owner, DefaultTexturePath, InLocation, InRotation, InScale, InSize, InAnimManager)
{
}

void SpriteSheet2DRendererComponent::Initialize()
{
	if (AnimManager) {
		AnimManager->ResetAnimationState();
	}
}

void SpriteSheet2DRendererComponent::Update(float DeltaTime)
{

	Vector3 DrawLocation = GetWorldLocation();
	Quaternion DrawRotation = GetWorldRotation();
	Vector2 SizeScaled = GetSizeScaledWithRatio();

	// No Idle Animation no more use Animation Manager
	if (AnimManager)
	{
		AnimManager->Update(DeltaTime);
		if (std::shared_ptr<SpriteSheet2DAnimation> CurrentAnimation = std::static_pointer_cast<SpriteSheet2DAnimation>(AnimManager->GetCurrentAnimation())) 
		{
			Rectangle Source = CurrentAnimation->GetAnimationSourceRect();

			if (DrawRotation.y < 0.0f != bIsDrawnInverted) 
			{
				Vector3 ActualLocation = GetComponentLocation();
				ActualLocation.x = -ActualLocation.x;
				SetComponentLocation(ActualLocation);
			}

			bIsDrawnInverted = DrawRotation.y < 0.0f;
			if (DrawRotation.y < 0.0f)
			{
				Source.width = -Source.width;
			}
			

			Rectangle Destination = {
				DrawLocation.x,
				DrawLocation.y,
				SizeScaled.x,
				SizeScaled.y
			};

			DrawTexturePro(CurrentAnimation->GetAnimationTexture(), Source, Destination, { SizeScaled.x / 2, SizeScaled.y / 2 }, DrawRotation.x, WHITE);
		}
		else
		{
			Renderer2DComponent::Update(DeltaTime);
		}
	}
	else 
	{
		Renderer2DComponent::Update(DeltaTime);
	}
}
