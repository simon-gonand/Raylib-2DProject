#include "Animation.h"
#include "Animation.h"
#include "Animation.h"
#include "Animation.h"
#include "Animation.h"
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
	for (DelegateBase<void, Animation*>* Delegate : OnAnimationDurationFinished)
	{
		Delegate->Invoke(this);
	}
}

void Animation::AnimationFinished()
{
	for (DelegateBase<void, Animation*>* Delegate : OnAnimationFinished)
	{
		Delegate->Invoke(this);
	}
}

bool Animation::IsAnimationFinished() const
{
	return false;
}
