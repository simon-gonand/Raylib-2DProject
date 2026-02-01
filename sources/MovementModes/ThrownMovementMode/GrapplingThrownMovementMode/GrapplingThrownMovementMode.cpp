#include "GrapplingThrownMovementMode.h"

GrapplingThrownMovementMode::GrapplingThrownMovementMode(std::shared_ptr<PhysicsComponent> OwnerPhysicsComponent, std::shared_ptr<MovementComponent> OwnerMovementComp)
	: ThrownMovementMode(OwnerPhysicsComponent, OwnerMovementComp)
{
}

void GrapplingThrownMovementMode::SetFinalLocation(const Vector3& InFinalLocation)
{
	FinalLocation = InFinalLocation;
}

void GrapplingThrownMovementMode::OnSwitch()
{
	// We don't want to override the friction on this movement mode
}

Vector3 GrapplingThrownMovementMode::PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity)
{
	if (FloatEquals(CurrentVelocity.y, 0.0f))
	{
		LastVelocityIncrease = CurrentVelocity;
		MovementComp->SwitchMovementMode(EMovementMode::GROUND);
	}
	else if (FloatEquals(CurrentVelocity.x, 0.0f))
	{
		LastVelocityIncrease = CurrentVelocity;
		MovementComp->SwitchMovementMode(EMovementMode::FALLING);
	}

	Vector3 DefaultResult = ThrownMovementMode::PerformMovement(DeltaTime, Input, CurrentVelocity);
	Vector3 OwnerLocation = MovementComp->GetOwner()->GetActorLocation();

	if (Vector3Distance(OwnerLocation, FinalLocation) < MinimalDistance)
	{
		LastVelocityIncrease = CurrentVelocity;
		MovementComp->SwitchMovementMode(EMovementMode::JUMPING);
		return DefaultResult;
	}

	Vector3 Direction = Vector3Subtract(FinalLocation, OwnerLocation);
	Direction = Vector3Normalize(Direction);
	return Vector3Scale(Direction, Speed);
}
