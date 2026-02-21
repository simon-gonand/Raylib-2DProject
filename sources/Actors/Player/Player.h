#pragma once

#include "../BaseClass/Actor.h"
#include "../../Components/Movements/MovementComponent.h"
#include "../../Components/Features/GrapplingHook/GrapplingHookComponent.h"

#include <box2d/box2d.h>
#include <unordered_map>
#include "../../Components/Renderer/2DRenderer/CableRenderer/CableRendererComponent.h"

enum class DeathReason : int
{
	FALLING,
	HIT
};

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

	void Die(DeathReason Reason);
	void Respawn();

	EMovementMode GetCurrentMovementMode() const;
	EMovementMode GetPreviousMovementMode() const;
	
	std::shared_ptr<class PhysicsComponent> GetPhysicsComponent();


	// Event Bindings
	template<class C, void (C::* Function)(int)>
	void BindOnIncrementJumpCount(C* Instance)
	{
		if (!OnIncrementJumpCount)
			OnIncrementJumpCount = new DelegateBase<void, int>();
		OnIncrementJumpCount->Bind<C, Function>(Instance);
	}

	template<class C, void (C::* Function)(DeathReason)>
	void BindOnDeath(C* Instance)
	{
		DelegateBase<void, DeathReason>* Delegate = new DelegateBase<void, DeathReason>();
		Delegate->Bind<C, Function>(Instance);
		OnDeath.push_back(Delegate);
	}

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

	DelegateBase<void, int>* OnIncrementJumpCount = nullptr;
	std::vector<DelegateBase<void, DeathReason>*> OnDeath;

	Vector3 ActorInitialPostion;

	EMovementMode CurrentMovementModeShape;
	
	void UpdateCollision();

	void OnMovementModeSwitch(EMovementMode PreviousMovementMode, EMovementMode CurrentMovementMode);
};

