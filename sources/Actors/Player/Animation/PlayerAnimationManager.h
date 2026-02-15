#pragma once

#include "../../../Animations/2D/SpriteSheet2DAnimationManager.h"

class PlayerAnimationManager : public SpriteSheet2DAnimationManager
{
public:
	void Initialize(std::shared_ptr<class Player> InPlayerOwner);

protected:
	virtual void Update(const float& DeltaTime) override;

private:
	std::shared_ptr<Player> Player;

	void ComputeDefaultAnimation();

	void OnEndSlideEnded(const std::shared_ptr<Animation> EndSlideAnimation);
	void OnIncrementJumpCount(int InJumpCount);
};