#pragma once

#include "../BaseClass/Actor.h"
#include "../../Components/Movements/MovementComponent.h"
#include "../../Components/Features/GrapplingHook/GrapplingHookComponent.h"

#include <box2d/box2d.h>
#include <unordered_map>
#include "../../Components/Renderer/2DRenderer/CableRenderer/CableRendererComponent.h"

class Player: public Actor
{
public:
	Player();
	virtual ~Player();

	virtual void Initialize() override;

	void Move(const Vector2& Scale);
	void Aim(const Vector2& Scale);
	void Jump(const float& Scale, const enum InputTrigger& Trigger);
	void Slide(const float& Scale, const enum InputTrigger& Trigger);
	void AttractHook(const float& Scale, const enum InputTrigger& Trigger);
	void ClearAttractHook(const float& Scale, const enum InputTrigger& Trigger);
	void BalanceHook(const float& Scale, const enum InputTrigger& Trigger);
	void ClearBalanceHook(const float& Scale, const enum InputTrigger& Trigger);

	virtual void Update(float DeltaTime) override;
	virtual void PostUpdate() override;

	void Respawn();

	EMovementMode GetCurrentMovementMode() const;
	EMovementMode GetPreviousMovementMode() const;
	
	std::shared_ptr<class PhysicsComponent> GetPhysicsComponent();

private:
	std::shared_ptr<class InputComponent> InputComp;
	std::shared_ptr<PhysicsComponent> PhysicsComp;
	std::shared_ptr<class PlayerCameraComponent> CameraComp;
	std::shared_ptr<class RendererComponent> RendererComp;
	std::shared_ptr<class MovementComponent> MovementComp;
	std::shared_ptr<GrapplingHookComponent<Renderer2DComponent, CableRendererComponent>> GrapplingHookComp;

	std::shared_ptr<class AnimationManager> CreatePlayerAnimationManager();

	std::unordered_map<EMovementMode, const b2Polygon > CollisionShapes;

	bool bCanIncrementJump = true;

	Vector3 ActorInitialPostion;

	void UpdateCollision();

	void OnMovementModeSwitch(EMovementMode PreviousMovementMode, EMovementMode CurrentMovementMode);
};

