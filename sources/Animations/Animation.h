#pragma once

#include <vector>

#include "../Utils/Delegates/DelegateBase/DelegateBase.h"

class Animation 
{
public:
	Animation(float InDuration = 1.0f, bool bInIsLooping = false);

	virtual void StartAnimation();
	virtual void Update(const float& DeltaTime);

	// Event Bindings
	template<class C, void (C::* Function)(Animation*)>
	void BindOnAnimationDurationFinished(C* Instance)
	{
		DelegateBase<void, const Animation*>* OnAnimationDurationFinishedDelegate = new DelegateBase<void, Animation*>();
		OnAnimationDurationFinishedDelegate->Bind<C, Function>(Instance);
		OnAnimationDurationFinished.push_back(OnAnimationDurationFinishedDelegate);
	}
	template<class C, void (C::* Function)(Animation*)>
	void BindOnAnimationFinished(C* Instance)
	{
		DelegateBase<void, const Animation*>* OnAnimationFinishedDelegate = new DelegateBase<void, Animation*>();
		OnAnimationFinishedDelegate->Bind<C, Function>(Instance);
		OnAnimationFinished.push_back(OnAnimationFinishedDelegate);
	}

protected:
	float Duration;
	float DurationLeft;

	bool bIsLooping = false;

	virtual void AnimationDurationFinished();
	virtual void AnimationFinished();
	virtual bool IsAnimationFinished() const;

private:
	std::vector<DelegateBase<void, Animation*>*> OnAnimationDurationFinished;
	std::vector<DelegateBase<void, Animation*>*> OnAnimationFinished;
};