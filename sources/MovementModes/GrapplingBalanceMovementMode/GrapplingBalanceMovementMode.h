#pragma once
#include "../MovementModeBase.h"
class GrapplingBalanceMovementMode : public MovementModeBase
{ 
public:
	GrapplingBalanceMovementMode(float InAcceleration, float InDeceleration, float InTopSpeed);

protected:
	virtual bool CanSwitchToMode(EMovementMode PreviousMovementMode, const Vector3& CurrentVelocity) const override;
};

