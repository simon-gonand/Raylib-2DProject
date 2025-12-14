#pragma once

#include "../BaseClass/Actor.h"
#include "../../Components/Movements/MovementComponent.h"

class Player: public Actor
{
public:
	Player();
	virtual ~Player();

	virtual void Initialize() override;

	void Move(const Vector2& Scale);
	void Jump(const float& Scale, const enum InputTrigger& Trigger);
	void Slide(const float& Scale, const enum InputTrigger& Trigger);

	virtual void Update(float DeltaTime) override;
	virtual void PostUpdate() override;

	EMovementMode GetCurrentMovementMode() const;
	EMovementMode GetPreviousMovementMode() const;
	
	std::shared_ptr<class PhysicsComponent> GetPhysicsComponent();

private:
	std::shared_ptr<class InputComponent> InputComp;
	std::shared_ptr<PhysicsComponent> PhysicsComp;
	std::shared_ptr<class PlayerCameraComponent> CameraComp;
	std::shared_ptr<class RendererComponent> RendererComp;
	std::shared_ptr<class MovementComponent> MovementComp;

	float JumpSpeed = -20.0f;

	bool bWasJumpingLastFrame = false;
	bool bIsJumping = false;

	void UpdateJumpVelocity(Vector2& NewVelocity);

	std::shared_ptr<class AnimationManager> CreatePlayerAnimationManager();
};

