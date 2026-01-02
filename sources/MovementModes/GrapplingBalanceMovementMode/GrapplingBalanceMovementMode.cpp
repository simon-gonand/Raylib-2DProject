#include "GrapplingBalanceMovementMode.h"

GrapplingBalanceMovementMode::GrapplingBalanceMovementMode(float InAcceleration, float InDeceleration, float InTopSpeed, std::shared_ptr<PhysicsComponent> InPhysicsComp, float InOverrideLinearDamping)
	: MovementModeBase(InAcceleration, InDeceleration, InTopSpeed), PhysicsComp{InPhysicsComp}, OverrideLinearDamping{InOverrideLinearDamping}
{
}

void GrapplingBalanceMovementMode::OnSwitch()
{
	BaseLinearDamping = PhysicsComp->GetLinearDamping();
	PhysicsComp->SetLinearDamping(OverrideLinearDamping);
}

bool GrapplingBalanceMovementMode::CanSwitchToMode(EMovementMode PreviousMovementMode, const Vector3& CurrentVelocity) const
{
	return MovementModeBase::CanSwitchToMode(PreviousMovementMode, CurrentVelocity) && 
		PreviousMovementMode != EMovementMode::THROWN && PreviousMovementMode != EMovementMode::GROUND && 
		PreviousMovementMode != EMovementMode::SLIDING;
}

Vector3 GrapplingBalanceMovementMode::PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity)
{
	if (Input.x != 0.0f)
		return { CurrentVelocity.x + (Input.x * DeltaTime * Acceleration), CurrentVelocity.y };
	return CurrentVelocity;
}

void GrapplingBalanceMovementMode::OnEndMovement()
{
	PhysicsComp->SetLinearDamping(BaseLinearDamping);
}
