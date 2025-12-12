#include "SpriteSheet2DAnimationManager.h"

#include <raylib.h>

#include "SpriteSheet2DAnimation.h"

void SpriteSheet2DAnimationManager::AddAnimationFromTexture(const char* AnimationStateName, const char* InAnimationTexturePath, int AnimationTextureNbFramePerRow, int AnimationTextureNbRow, float InDuration, bool bInIsLooping, int InFirstFrameIndex, int InLastFrameIndex, const char* AutomaticNextAnimationState)
{
	std::shared_ptr<Animation> NewAnim = AddAnimationFromTexture_Internal(AnimationStateName, InAnimationTexturePath, AnimationTextureNbFramePerRow, AnimationTextureNbRow, InDuration, bInIsLooping, InFirstFrameIndex, InLastFrameIndex);
	if (NewAnim)
	{
		NewAnim->BindOnAnimationFinished<SpriteSheet2DAnimationManager, &SpriteSheet2DAnimationManager::AutomaticNextState>(this);
		AutomaticNextStateMap.insert({ AnimationStateName, AutomaticNextAnimationState });
	}
}

void SpriteSheet2DAnimationManager::AutomaticNextState(const std::shared_ptr<Animation> FinishedAnimation)
{
	auto NextState = AutomaticNextStateMap.find(CurrentAnimationState);
	if (NextState != AutomaticNextStateMap.end()) {
		SetCurrentAnimationState(NextState->second);
	}
}

std::shared_ptr<Animation> SpriteSheet2DAnimationManager::AddAnimationFromTexture_Internal(const char* AnimationStateName, const char* InAnimationTexturePath, int AnimationTextureNbFramePerRow, int AnimationTextureNbRow, float InDuration, bool bInIsLooping, int InFirstFrameIndex, int InLastFrameIndex)
{
	Texture2D AnimationTexture = LoadTexture(InAnimationTexturePath);
	if (AnimationTexture.width > 0.0f && AnimationTexture.height > 0.0f)
	{
		std::shared_ptr<SpriteSheet2DAnimation> Animation = std::make_shared<SpriteSheet2DAnimation>(AnimationTexture, AnimationTextureNbFramePerRow, AnimationTextureNbRow, InDuration, bInIsLooping, InFirstFrameIndex, InLastFrameIndex);
		AddAnimation(AnimationStateName, Animation);
		return Animation;
	}

	return nullptr;
}