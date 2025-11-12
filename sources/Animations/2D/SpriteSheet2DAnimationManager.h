#pragma once

#include "../AnimationManager.h"

class SpriteSheet2DAnimationManager : public AnimationManager
{
public:
	void AddAnimationFromTexture(const char* AnimationStateName, const char* InAnimationTexturePath, int AnimationTextureNbFramePerRow = 1, int AnimationTextureNbRow = 1, float InDuration = 1.0f, bool bInIsLooping = false, int InFirstFrameIndex = 0, int InLastFrameIndex = 0);
};