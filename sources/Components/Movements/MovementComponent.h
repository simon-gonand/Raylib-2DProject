#pragma once

#include "../BaseClass/ComponentBase.h"

#include <unordered_map>
#include "../Physics/PhysicsComponent.h"

enum class EMovementMode : int
{
	NONE, // First MovementMode
	GROUND,
	FALLING,
	SLIDING
};

class MovementComponent : public ComponentBase
{
public:
	MovementComponent(std::shared_ptr<Actor> Owner, std::shared_ptr<PhysicsComponent> InOwnerPhysicsComponent);

	const Vector3& GetMovementVelocity();

	EMovementMode GetCurrentMovementMode();
	EMovementMode GetPreviousMovementMode();

	void SetMovementInput(const Vector2& Input);

	void SwitchMovementMode(EMovementMode NewMovementMode);

	void AddNewMovementMode(EMovementMode NewMovementMode, std::shared_ptr<class MovementModeBase> NewMovementModeObj);

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
};