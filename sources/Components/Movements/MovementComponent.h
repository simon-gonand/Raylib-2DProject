#pragma once

#include "../BaseClass/ComponentBase.h"

#include <unordered_map>
#include "../Physics/PhysicsComponent.h"

enum class EMovementMode : int
{
	NONE, // First MovementMode
	GROUND,
	JUMPING,
	FALLING,
	SLIDING,
	THROWN,
	GRAPPLING_THROWN,
	GRAPPLING_BALANCE
};

class MovementComponent : public ComponentBase
{
public:
	MovementComponent(std::shared_ptr<Actor> Owner, std::shared_ptr<PhysicsComponent> InOwnerPhysicsComponent, bool bAutoActivate = true);

	const Vector3& GetMovementVelocity();

	EMovementMode GetCurrentMovementMode();
	EMovementMode GetPreviousMovementMode();

	void SetMovementInput(const Vector2& Input);

	void SwitchMovementMode(EMovementMode NewMovementMode);

	void AddNewMovementMode(EMovementMode NewMovementMode, std::shared_ptr<class MovementModeBase> NewMovementModeObj);

	void DeactivateMovementMode(EMovementMode MovementModeToDeactivate);
	void ActivateMovementMode(EMovementMode MovementModeToActivate);
	bool IsMovementModeActivated(EMovementMode MovementModeToCheck) const;

	float GetCurrentMovementTopSpeed() const;

	template<class C, void (C::* Function)(EMovementMode, EMovementMode)>
	DelegateBase<void, EMovementMode, EMovementMode>* BindToOnMovementModeSwitch(C* Instance)
	{
		DelegateBase<void, EMovementMode, EMovementMode>* Delegate = new DelegateBase<void, EMovementMode, EMovementMode>();
		Delegate->Bind<C, Function>(Instance);
		OnMovementModeSwitches.push_back(Delegate);
		return Delegate;
	}

	void UnbindToOnMovementModeSwitch(DelegateBase<void, EMovementMode, EMovementMode>* DelegateToUnbind);
	
	void BroadcastOnMovementModeSwitch();

protected:
	virtual void Update(float DeltaTime) override;

private:
	std::shared_ptr<PhysicsComponent> OwnerPhysicsComponent;

	std::shared_ptr<MovementModeBase> CurrentMovementModeObj;
	EMovementMode CurrentMovementMode;
	EMovementMode PreviousMovementMode;
	Vector3 MovementVelocity;

	Vector2 MovementInput;

	std::unordered_map<EMovementMode, std::shared_ptr<MovementModeBase>> MovementModes;

	std::vector<DelegateBase<void, EMovementMode, EMovementMode>*> OnMovementModeSwitches;
};