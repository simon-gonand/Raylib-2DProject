#include "GrapplingThrownMovementMode.h"

GrapplingThrownMovementMode::GrapplingThrownMovementMode(std::shared_ptr<PhysicsComponent> OwnerPhysicsComponent, std::shared_ptr<MovementComponent> OwnerMovementComp, const float& InAcceleration, const float& InTopSpeed, const float& InEndDistance, const float& InVelocityLerpSpeed)
	: ThrownMovementMode(OwnerPhysicsComponent, OwnerMovementComp), Acceleration{InAcceleration}, TopSpeed{InTopSpeed}, EndDistance{InEndDistance}, VelocityLerpAlpha{0.0f}, VelocityLerpSpeed{InVelocityLerpSpeed}
{
}

void GrapplingThrownMovementMode::SetFinalLocation(const Vector3& InFinalLocation)
{
	if (!MovementComp || !MovementComp->GetOwner())
		return;
	
	FinalLocation = InFinalLocation;
	
	FinalDirection= Vector3Subtract(FinalLocation, MovementComp->GetOwner()->GetActorLocation());
	FinalDirection = Vector3Normalize(FinalDirection);
}

void GrapplingThrownMovementMode::OnSwitch()
{
	// We don't want to override the friction on this movement mode
	CurrentSpeed = 0.0f;
	FinalDirection = Vector3Zero();
	VelocityLerpAlpha = 0.0f;
}

Vector3 GrapplingThrownMovementMode::PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity)
{
	if (FloatEquals(CurrentVelocity.y, 0.0f))
	{
		MovementComp->SwitchMovementMode(EMovementMode::GROUND);
	}
	else if (FloatEquals(CurrentVelocity.x, 0.0f))
	{
		MovementComp->SwitchMovementMode(EMovementMode::FALLING);
	}

	Vector3 DefaultResult = ThrownMovementMode::PerformMovement(DeltaTime, Input, CurrentVelocity);
	Vector3 OwnerLocation = MovementComp->GetOwner()->GetActorLocation();

	if (Vector3Distance(OwnerLocation, FinalLocation) < EndDistance)
	{
		MovementComp->SwitchMovementMode(EMovementMode::JUMPING);
		return DefaultResult;
	}

	if (VelocityLerpAlpha < 1.0f)
	{
		VelocityLerpAlpha += DeltaTime * VelocityLerpSpeed;
		VelocityLerpAlpha = VelocityLerpAlpha > 1.0f ? 1.0f : VelocityLerpAlpha;
	}
	
	Vector3 CurrentVelocityDirection = Vector3Normalize(CurrentVelocity);

	CurrentSpeed += Acceleration * DeltaTime;
	CurrentSpeed = CurrentSpeed > TopSpeed ? TopSpeed : CurrentSpeed;
	
	Vector3 TargetVelocity = Vector3Scale(FinalDirection, CurrentSpeed);
	return VelocityLerpAlpha == 1.0f ? TargetVelocity : Vector3Lerp(Vector3Scale(CurrentVelocityDirection, CurrentSpeed), TargetVelocity, VelocityLerpAlpha);
}
