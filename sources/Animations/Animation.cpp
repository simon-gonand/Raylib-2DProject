#include "Animation.h"

Animation::Animation(float InDuration, bool bInIsLooping) 
{
	Duration = InDuration;
	DurationLeft = Duration;
	bIsLooping = bInIsLooping;
}

void Animation::StartAnimation()
{
	DurationLeft = Duration;
}

void Animation::Update(const float& DeltaTime)
{
	DurationLeft -= DeltaTime;
	if (DurationLeft <= 0.0f) 
	{
		DurationLeft = Duration;
		AnimationDurationFinished();
		if (IsAnimationFinished()) 
		{
			if (bIsLooping) 
			{
				StartAnimation();
			}
			else 
			{
				AnimationFinished();
			}
		}
	}
}

void Animation::AnimationDurationFinished()
{
	for (DelegateBase<void, const std::shared_ptr<Animation>>* Delegate : OnAnimationDurationFinished)
	{
		Delegate->Invoke(shared_from_this());
	}
}

void Animation::AnimationFinished()
{
	for (DelegateBase<void, const std::shared_ptr<Animation>>* Delegate : OnAnimationFinished)
	{
		Delegate->Invoke(shared_from_this());
	}
}

bool Animation::IsAnimationFinished() const
{
	return false;
}
