#include "PlayerAnimationManager.h"

#include "../Player.h"
#include "../../../Components/Physics/PhysicsComponent.h"

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
		if (std::shared_ptr<PhysicsComponent> PlayerPhysicsComponent = Player->GetPhysicsComponent()) {
			Vector2 LinearVelocity = PlayerPhysicsComponent->GetLinearVelocity();
			if (!FloatEquals(LinearVelocity.x, 0.0f)) {
				SetCurrentAnimationState("Movement");
			}
			else {
				SetCurrentAnimationState("Idle");
			}
		}
		else {
			SetCurrentAnimationState("Idle");
		}
	}

	SpriteSheet2DAnimationManager::Update(DeltaTime);
}