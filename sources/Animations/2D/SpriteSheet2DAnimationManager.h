#pragma once

#include "../AnimationManager.h"

class SpriteSheet2DAnimationManager : public AnimationManager
{
public:
	void AddAnimationFromTexture(const char* AnimationStateName, const char* InAnimationTexturePath, int AnimationTextureNbFramePerRow = 1, 
		int AnimationTextureNbRow = 1, float InDuration = 1.0f, bool bInIsLooping = false, int InFirstFrameIndex = 0, int InLastFrameIndex = 0, const char* AutomaticNextAnimationState = nullptr);

	template<class C, void (C::* EndAnimationCallback)(const std::shared_ptr<Animation>)>
	void AddAnimationFromTexture(const char* AnimationStateName, const char* InAnimationTexturePath, int AnimationTextureNbFramePerRow = 1,
		int AnimationTextureNbRow = 1, float InDuration = 1.0f, bool bInIsLooping = false, int InFirstFrameIndex = 0, int InLastFrameIndex = 0, C* Instance = nullptr)
	{
		std::shared_ptr<Animation> NewAnim = AddAnimationFromTexture_Internal(AnimationStateName, InAnimationTexturePath, AnimationTextureNbFramePerRow, AnimationTextureNbRow, InDuration, bInIsLooping, InFirstFrameIndex, InLastFrameIndex);
		if (NewAnim)
		{
			NewAnim->BindOnAnimationFinished<C, EndAnimationCallback>(Instance);
		}
	}

private:
	std::unordered_map<const char*, const char*> AutomaticNextStateMap; 

	void AutomaticNextState(const std::shared_ptr<Animation> FinishedAnimation);

	std::shared_ptr<Animation> AddAnimationFromTexture_Internal(const char* AnimationStateName, const char* InAnimationTexturePath, int AnimationTextureNbFramePerRow = 1,
		int AnimationTextureNbRow = 1, float InDuration = 1.0f, bool bInIsLooping = false, int InFirstFrameIndex = 0, int InLastFrameIndex = 0);
};