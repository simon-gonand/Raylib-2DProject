#include "PlayerAnimationManager.h"

#include "../Player.h"

void PlayerAnimationManager::Initialize(std::shared_ptr<class Player> InPlayerOwner)
{
	Player = InPlayerOwner;
}

void PlayerAnimationManager::Update(const float& DeltaTime)
{
	if (!Player)
		return;

	if (Player->GetCurrentMovementMode() == EMovementMode::FALLING) {
		SetCurrentAnimationState("Jump");
	}
	else {
		SetCurrentAnimationState("Idle");
	}

	SpriteSheet2DAnimationManager::Update(DeltaTime);
}