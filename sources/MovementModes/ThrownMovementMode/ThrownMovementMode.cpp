#include "ThrownMovementMode.h"

ThrownMovementMode::ThrownMovementMode(std::shared_ptr<PhysicsComponent> OwnerPhysicsComponent, std::shared_ptr<MovementComponent> OwnerMovementComp, float InFrictionOverride)
    : MovementModeBase(0.0f, 0.0f, 0.0f), FrictionOverride{InFrictionOverride}
{
    PhysicsComp = OwnerPhysicsComponent;
    MovementComp = OwnerMovementComp;
}

void ThrownMovementMode::OnSwitch()
{
    BaseFriction = PhysicsComp->GetFriction();
    PhysicsComp->SetFriction(FrictionOverride);
}

Vector3 ThrownMovementMode::PerformMovement(float DeltaTime, const Vector2& Input, const Vector3& CurrentVelocity)
{
    // No input available

    if (Vector3Equals(CurrentVelocity, Vector3Zero()))
    {
        MovementComp->SwitchMovementMode(EMovementMode::GROUND);
        PhysicsComp->SetFriction(BaseFriction);
    }

    return CurrentVelocity;
}