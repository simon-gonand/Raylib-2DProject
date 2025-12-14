#pragma once

#include "../MovementModeBase.h"

class GroundMovementMode : public MovementModeBase
{
public:
	GroundMovementMode(float InAcceleration, float InDeceleration, float InTopSpeed);

protected:
	virtual bool CanSwitchToMode(EMovementMode CurrentMovementMode) const override;
};