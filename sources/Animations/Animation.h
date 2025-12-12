#pragma once

#include <vector>
#include <memory>

#include "../Utils/Delegates/DelegateBase/DelegateBase.h"

class Animation : public std::enable_shared_from_this<Animation>
{
public:
	Animation(float InDuration = 1.0f, bool bInIsLooping = false);

	virtual void StartAnimation();
	virtual void Update(const float& DeltaTime);

	// Event Bindings
	template<class C, void (C::* Function)(const std::shared_ptr<Animation>)>
	void BindOnAnimationDurationFinished(C* Instance)
	{
		DelegateBase<void, const std::shared_ptr<Animation>>* OnAnimationDurationFinishedDelegate = new DelegateBase<void, const std::shared_ptr<Animation>>();
		OnAnimationDurationFinishedDelegate->Bind<C, Function>(Instance);
		OnAnimationDurationFinished.push_back(OnAnimationDurationFinishedDelegate);
	}
	template<class C, void (C::* Function)(const std::shared_ptr<Animation>)>
	void BindOnAnimationFinished(C* Instance)
	{
		DelegateBase<void, const std::shared_ptr<Animation>>* OnAnimationFinishedDelegate = new DelegateBase<void, const std::shared_ptr<Animation>>();
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
	std::vector<DelegateBase<void, const std::shared_ptr<Animation>>*> OnAnimationDurationFinished;
	std::vector<DelegateBase<void, const std::shared_ptr<Animation>>*> OnAnimationFinished;
};