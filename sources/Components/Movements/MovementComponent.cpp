#include "MovementComponent.h"

#include "../../MovementModes/MovementModeBase.h"
#include "../Helpers/Math/Vectors/Vectors.h"

#include <raymath.h>

MovementComponent::MovementComponent(std::shared_ptr<Actor> Owner, std::shared_ptr<PhysicsComponent> InOwnerPhysicsComponent)
	: ComponentBase(Owner), OwnerPhysicsComponent{InOwnerPhysicsComponent}
{
	MovementVelocity = Vector3Zero();
	CurrentMovementMode = EMovementMode::NONE;
	PreviousMovementMode = EMovementMode::NONE;
	MovementInput = Vector2Zero();
}

const Vector3& MovementComponent::GetMovementVelocity()
{
	return MovementVelocity;
}

EMovementMode MovementComponent::GetCurrentMovementMode()
{
	return CurrentMovementMode;
}

EMovementMode MovementComponent::GetPreviousMovementMode()
{
	return PreviousMovementMode;
}

void MovementComponent::SetMovementInput(const Vector2& Input)
{
	MovementInput = Input;
}

void MovementComponent::SwitchMovementMode(EMovementMode NewMovementMode)
{
	if (NewMovementMode == CurrentMovementMode)
		return;

	auto NewMovementModeObj = MovementModes.find(NewMovementMode);
	if (NewMovementModeObj != MovementModes.end() && 
		(CurrentMovementMode == EMovementMode::NONE || NewMovementModeObj->second->CanSwitchToMode(CurrentMovementMode, OwnerPhysicsComponent->GetLinearVelocity())))
	{
		PreviousMovementMode = CurrentMovementMode;
		CurrentMovementMode = NewMovementMode;
		CurrentMovementModeObj = NewMovementModeObj->second;
		CurrentMovementModeObj->OnSwitch();
	}
}

void MovementComponent::AddNewMovementMode(EMovementMode NewMovementMode, std::shared_ptr<MovementModeBase> NewMovementModeObj)
{
	if(NewMovementMode != EMovementMode::NONE && NewMovementModeObj)
		MovementModes.insert({ NewMovementMode, NewMovementModeObj });
}

void MovementComponent::Update(float DeltaTime)
{
	if (CurrentMovementModeObj)
	{
		MovementVelocity = CurrentMovementModeObj->PerformMovement(DeltaTime, MovementInput, OwnerPhysicsComponent->GetLinearVelocity());
		OwnerPhysicsComponent->SetLinearVelocity(MovementVelocity);
	}
}