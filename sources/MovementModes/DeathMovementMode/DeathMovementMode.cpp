#include "DeathMovementMode.h"

DeathMovementMode::DeathMovementMode():
	MovementModeBase(0.0f, 0.0f, 0.0f)
{
}

Vector3 DeathMovementMode::PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity)
{
	return Vector3Zero();
}
