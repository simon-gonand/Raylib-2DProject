#include "PlayerAnimationManager.h"

#include "../Player.h"
#include "../../../Components/Physics/PhysicsComponent.h"

void PlayerAnimationManager::Initialize(std::shared_ptr<class Player> InPlayerOwner)
{
	Player = InPlayerOwner;
	Player->BindOnIncrementJumpCount<PlayerAnimationManager, &PlayerAnimationManager::OnIncrementJumpCount>(this);
	Player->BindOnDeath<PlayerAnimationManager, &PlayerAnimationManager::OnDeath>(this);

	AddAnimationFromTexture("Idle", "assets/Characters/Player/SpriteSheets/_Idle.png", 10, 1, 0.1f, true, 0, 9, "");
	AddAnimationFromTexture("Jump", "assets/Characters/Player/SpriteSheets/_Jump.png", 3, 1, 0.05f, true, 0, 2, "");
	AddAnimationFromTexture("SecondJump", "assets/Characters/Player/SpriteSheets/_Roll.png", 12, 1, 0.025f, false, 0, 11, "Jump");
	AddAnimationFromTexture("Movement", "assets/Characters/Player/SpriteSheets/_Run.png", 10, 1, 0.025f, true, 0, 9, "");
	AddAnimationFromTexture("StartSlide", "assets/Characters/Player/SpriteSheets/_SlideTransitionStart.png", 1, 1, 0.1f, false, 0, 0, "Slide");
	AddAnimationFromTexture("Slide", "assets/Characters/Player/SpriteSheets/_Slide.png", 2, 1, 0.05f, true, 0, 1, "");
	AddAnimationFromTexture<PlayerAnimationManager, &PlayerAnimationManager::OnEndDeath>("Death", "assets/Characters/Player/SpriteSheets/_Death.png", 10, 1, 0.05f, false, 0, 9, this);
	AddAnimationFromTexture<PlayerAnimationManager, &PlayerAnimationManager::OnEndSlideEnded>("EndSlide", "assets/Characters/Player/SpriteSheets/_SlideTransitionEnd.png", 1, 1, 0.15f, false, 0, 0, this);
}

void PlayerAnimationManager::Update(const float& DeltaTime)
{
	if (!Player)
		return;

	if (Player->GetCurrentMovementMode() != EMovementMode::DEAD)
	{
		if (Player->GetCurrentMovementMode() == EMovementMode::FALLING || Player->GetCurrentMovementMode() == EMovementMode::JUMPING)
		{
			if (CurrentAnimationState != "SecondJump")
				SetCurrentAnimationState("Jump");
		}
		else if (Player->GetCurrentMovementMode() == EMovementMode::SLIDING) {
			if (Player->GetPreviousMovementMode() != EMovementMode::SLIDING && CurrentAnimationState != "Slide")
				SetCurrentAnimationState("StartSlide");
		}
		else if (Player->GetPreviousMovementMode() == EMovementMode::SLIDING && CurrentAnimationState == "Slide")
		{
			SetCurrentAnimationState("EndSlide");
		}
		else if (CurrentAnimationState != "EndSlide") {
			ComputeDefaultAnimation();
		}
	}

	SpriteSheet2DAnimationManager::Update(DeltaTime);
}

void PlayerAnimationManager::ComputeDefaultAnimation()
{
	if (std::shared_ptr<PhysicsComponent> PlayerPhysicsComponent = Player->GetPhysicsComponent()) {
		Vector3 LinearVelocity = PlayerPhysicsComponent->GetLinearVelocity();
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

void PlayerAnimationManager::OnEndSlideEnded(const std::shared_ptr<Animation> EndSlideAnimation)
{
	ComputeDefaultAnimation();
}

void PlayerAnimationManager::OnEndDeath(const std::shared_ptr<Animation> EndDeathAnimation)
{
	if (Player)
	{
		Player->Respawn();
		SetCurrentAnimationState("Idle");
	}
}

void PlayerAnimationManager::OnIncrementJumpCount(int InJumpCount)
{
	if (InJumpCount > 1)
	{
		SetCurrentAnimationState("SecondJump");
	}
}

void PlayerAnimationManager::OnDeath(DeathReason Reason)
{
	switch (Reason)
	{
	case DeathReason::HIT:
		SetCurrentAnimationState("Death");
		break;
	default:
		break;
	}
}
