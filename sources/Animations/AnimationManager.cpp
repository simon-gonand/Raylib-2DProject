#include "AnimationManager.h"

void AnimationManager::AddAnimation(const char* AnimationName, std::shared_ptr<Animation> AnimationToAdd)
{
	if (!AnimationToAdd || !AnimationName || AnimationName[0] == '\0')
		return;

	AnimationBank.insert({ AnimationName, AnimationToAdd });
	if (!InitialAnimationState || InitialAnimationState[0] == '\0')
		InitialAnimationState = AnimationName;
}

void AnimationManager::SetCurrentAnimationState(const char* AnimationState)
{
	if (AnimationState && AnimationState == CurrentAnimationState)
		return;

	auto Anim = AnimationBank.find(AnimationState);
	if (Anim != AnimationBank.end()) 
	{
		CurrentAnimationState = AnimationState;
		CurrentPlayedAnimation = Anim->second;
		CurrentPlayedAnimation->StartAnimation();
	}
}

const char* AnimationManager::GetCurrentAnimationState() const
{
	return CurrentAnimationState;
}

std::shared_ptr<Animation> AnimationManager::GetCurrentAnimation() const
{
	return CurrentPlayedAnimation;
}

void AnimationManager::ResetAnimationState()
{
	CurrentAnimationState = InitialAnimationState;
	CurrentPlayedAnimation = AnimationBank[CurrentAnimationState];
	CurrentPlayedAnimation->StartAnimation();
}

void AnimationManager::Update(const float& DeltaTime)
{
	if (CurrentPlayedAnimation) 
	{
		CurrentPlayedAnimation->Update(DeltaTime);
	}
}
