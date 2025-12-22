#include "MovementComponent.h"

#include "../../MovementModes/MovementModeBase.h"
#include "../Helpers/Math/Vectors/Vectors.h"

#include <raymath.h>

MovementComponent::MovementComponent(std::shared_ptr<Actor> Owner, std::shared_ptr<PhysicsComponent> InOwnerPhysicsComponent, bool bAutoActivate)
	: ComponentBase(Owner, bAutoActivate), OwnerPhysicsComponent{InOwnerPhysicsComponent}
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

void MovementComponent::DeactivateMovementMode(EMovementMode MovementModeToDeactivate)
{
	auto MovementMode = MovementModes.find(MovementModeToDeactivate);
	if (MovementMode != MovementModes.end() && MovementMode->second)
	{
		MovementMode->second->Deactivate();
	}
}

void MovementComponent::ActivateMovementMode(EMovementMode MovementModeToActivate)
{
	auto MovementMode = MovementModes.find(MovementModeToActivate);
	if (MovementMode != MovementModes.end() && MovementMode->second)
	{
		MovementMode->second->Activate();
	}
}

bool MovementComponent::IsMovementModeActivated(EMovementMode MovementModeToCheck) const
{
	auto MovementMode = MovementModes.find(MovementModeToCheck);
	if (MovementMode != MovementModes.end() && MovementMode->second)
	{
		return MovementMode->second->IsActive();
	}
	return false;
}

float MovementComponent::GetCurrentMovementTopSpeed() const
{
	if (CurrentMovementModeObj) 
	{
		return CurrentMovementModeObj->GetTopSpeed();
	}
	return 0.0f;
}

void MovementComponent::Update(float DeltaTime)
{
	ComponentBase::Update(DeltaTime);

	if (CurrentMovementModeObj)
	{
		MovementVelocity = CurrentMovementModeObj->PerformMovement(DeltaTime, MovementInput, OwnerPhysicsComponent->GetLinearVelocity());
		OwnerPhysicsComponent->SetLinearVelocity(MovementVelocity);
	}
}