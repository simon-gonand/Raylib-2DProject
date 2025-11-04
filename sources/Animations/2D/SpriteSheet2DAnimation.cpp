#include "SpriteSheet2DAnimation.h"

SpriteSheet2DAnimation::SpriteSheet2DAnimation(const Texture2D& InAnimationTexture, int AnimationTextureNbFramePerRow, int AnimationTextureNbRow,
	float InDuration, bool bInIsLooping, int InFirstFrameIndex, int InLastFrameIndex):
	Animation(InDuration, bInIsLooping)
{
	TextureInfo = AnimationTextureInfo();
	TextureInfo.AnimationTexture = InAnimationTexture;
	TextureInfo.NbFramePerRow = AnimationTextureNbFramePerRow;
	TextureInfo.NbRow = AnimationTextureNbRow;

	FirstFrameIndex = InFirstFrameIndex;
	LastFrameIndex = InLastFrameIndex;
	CurrentFrameIndex = FirstFrameIndex;
}

Rectangle SpriteSheet2DAnimation::GetAnimationSourceRect() const
{
	float FrameWidth = TextureInfo.AnimationTexture.width / TextureInfo.NbFramePerRow;
	float FrameHeight = TextureInfo.AnimationTexture.height / TextureInfo.NbRow;
	return Rectangle
	{
		(CurrentFrameIndex % TextureInfo.NbFramePerRow) * FrameWidth,
		(CurrentFrameIndex / TextureInfo.NbFramePerRow) * FrameHeight,
		FrameWidth,
		FrameHeight
	};
}

const Texture2D& SpriteSheet2DAnimation::GetAnimationTexture() const
{
	return TextureInfo.AnimationTexture;
}

void SpriteSheet2DAnimation::StartAnimation()
{
	Animation::StartAnimation();
	CurrentFrameIndex = FirstFrameIndex;
}

void SpriteSheet2DAnimation::AnimationDurationFinished()
{
	Animation::AnimationDurationFinished();
	++CurrentFrameIndex;
}

bool SpriteSheet2DAnimation::IsAnimationFinished() const
{
	return CurrentFrameIndex - 1 == LastFrameIndex;
}
