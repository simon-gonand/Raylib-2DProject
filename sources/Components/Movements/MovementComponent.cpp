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

std::shared_ptr<MovementModeBase> MovementComponent::GetCurrentMovementModeObj() const
{
	return CurrentMovementModeObj;
}

std::shared_ptr<MovementModeBase> MovementComponent::GetMovementModeObj(EMovementMode MovementMode) const
{
	auto MovementModeObjIt = MovementModes.find(MovementMode);
	if (MovementModeObjIt != MovementModes.end())
		return MovementModeObjIt->second;
	return nullptr;
}

void MovementComponent::SetMovementInput(const Vector2& Input)
{
	MovementInput = Input;
}

bool MovementComponent::SwitchMovementMode(EMovementMode NewMovementMode)
{
	if (NewMovementMode == CurrentMovementMode)
		return false;

	auto NewMovementModeObj = MovementModes.find(NewMovementMode);
	if (NewMovementModeObj != MovementModes.end() && 
		(CurrentMovementMode == EMovementMode::NONE || NewMovementModeObj->second->CanSwitchToMode(CurrentMovementMode, OwnerPhysicsComponent->GetLinearVelocity())))
	{
		PreviousMovementMode = CurrentMovementMode;
		CurrentMovementMode = NewMovementMode;
		CurrentMovementModeObj = NewMovementModeObj->second;
		CurrentMovementModeObj->OnSwitch();
		BroadcastOnMovementModeSwitch();

		return true;
	}

	return false;
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

void MovementComponent::UnbindToOnMovementModeSwitch(DelegateBase<void, EMovementMode, EMovementMode>* DelegateToUnbind)
{
	std::vector<DelegateBase<void, EMovementMode, EMovementMode>*>::iterator ToRemove = std::find(OnMovementModeSwitches.begin(), OnMovementModeSwitches.end(), DelegateToUnbind);
	if (ToRemove != OnMovementModeSwitches.end()) 
	{
		OnMovementModeSwitches.erase(ToRemove);
	}
}

void MovementComponent::BroadcastOnMovementModeSwitch()
{
	for (DelegateBase<void, EMovementMode, EMovementMode>* Delegate : OnMovementModeSwitches)
	{
		Delegate->Invoke(PreviousMovementMode, CurrentMovementMode);
	}
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

void MovementComponent::DrawDebug(float DeltaTime)
{
	const char* CurrentMovementModeStr = DebugMovementModeStr(CurrentMovementMode);
	DrawText(TextFormat("Current Movement Mode: %s", CurrentMovementModeStr), 0, 0, 10, GREEN);
	const char* PreviousMovementModeStr = DebugMovementModeStr(PreviousMovementMode);
	DrawText(TextFormat("Previous Movement Mode: %s", PreviousMovementModeStr), 0, 10, 10, ORANGE);
}

const char* MovementComponent::DebugMovementModeStr(EMovementMode InMovementMode) const
{
	switch (InMovementMode)
	{
	case EMovementMode::GROUND:
		return "GROUND";
	case EMovementMode::JUMPING:
		return "JUMPING";
	case EMovementMode::FALLING:
		return "FALLING";
	case EMovementMode::SLIDING:
		return "SLIDING";
	case EMovementMode::THROWN:
		return "THROWN";
	case EMovementMode::GRAPPLING_THROWN:
		return "GRAPPLING THROWN";
	case EMovementMode::GRAPPLING_BALANCE:
		return "GRAPPLING BALANCE";
	default:
		return "";
	}
}
