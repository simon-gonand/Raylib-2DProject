#include "SpriteSheet2DAnimationManager.h"

#include <raylib.h>

#include "SpriteSheet2DAnimation.h"

void SpriteSheet2DAnimationManager::AddAnimationFromTexture(const char* AnimationStateName, const char* InAnimationTexturePath, int AnimationTextureNbFramePerRow, int AnimationTextureNbRow, float InDuration, bool bInIsLooping, int InFirstFrameIndex, int InLastFrameIndex)
{
	Texture2D AnimationTexture = LoadTexture(InAnimationTexturePath);
	if (AnimationTexture.width > 0.0f && AnimationTexture.height > 0.0f)
	{
		std::shared_ptr<SpriteSheet2DAnimation> Animation = std::make_shared<SpriteSheet2DAnimation>(AnimationTexture, AnimationTextureNbFramePerRow, AnimationTextureNbRow, InDuration, bInIsLooping, InFirstFrameIndex, InLastFrameIndex);
		AddAnimation(AnimationStateName, Animation);
	}
}
