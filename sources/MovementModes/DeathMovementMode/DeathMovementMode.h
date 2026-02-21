#pragma once

#include "../MovementModeBase.h"

class DeathMovementMode : public MovementModeBase
{
public:
	DeathMovementMode();

protected:
	virtual Vector3 PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity) override;
};