#pragma once

#include "../Animation.h"

#include <raylib.h>

struct AnimationTextureInfo
{
	Texture2D AnimationTexture;
	int NbFramePerRow = 1;
	int NbRow = 1;
};

class SpriteSheet2DAnimation : public Animation
{
public:
	SpriteSheet2DAnimation(const Texture2D& InAnimationTexture, int AnimationTextureNbFramePerRow = 1, int AnimationTextureNbRow = 1, float InDuration = 1.0f, bool bInIsLooping = false, int InFirstFrameIndex = 0, int InLastFrameIndex = 0);

	Rectangle GetAnimationSourceRect() const;
	const Texture2D& GetAnimationTexture() const;

	virtual void StartAnimation() override;

protected:
	virtual void AnimationDurationFinished() override;

	virtual bool IsAnimationFinished() const override;
	
private:
	AnimationTextureInfo TextureInfo;

	int FirstFrameIndex;
	int LastFrameIndex;
	int CurrentFrameIndex;
};