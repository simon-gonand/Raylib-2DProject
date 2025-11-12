#pragma once

#include <unordered_map>
#include <memory>

#include "Animation.h"

class AnimationManager
{
public:
	void AddAnimation(const char* AnimationName, std::shared_ptr<Animation> AnimationToAdd);

	void SetCurrentAnimationState(const char* AnimationState);
	std::shared_ptr<Animation> GetCurrentAnimation() const;
	void ResetAnimationState();

	virtual void Update(const float& DeltaTime);

protected:
	const char* CurrentAnimationState = nullptr;

private:
	std::unordered_map<const char*, std::shared_ptr<Animation>> AnimationBank;

	std::shared_ptr<Animation> CurrentPlayedAnimation = nullptr;

	const char* InitialAnimationState = nullptr;
};