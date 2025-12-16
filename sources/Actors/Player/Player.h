#pragma once

#include "../BaseClass/Actor.h"
#include "../../Components/Movements/MovementComponent.h"

#include <box2d/box2d.h>
#include <unordered_map>

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

	std::shared_ptr<class AnimationManager> CreatePlayerAnimationManager();

	std::unordered_map<EMovementMode, std::shared_ptr<b2Shape>> CollisionShapes;

	float TimeBeforeActivateSliding = 0.5f;
	float CurrentTimeBeforeActivateSliding = 0.0f;

	void UpdateCollision();
	void UpdateSlidingAvailability(float DeltaTime);
};

