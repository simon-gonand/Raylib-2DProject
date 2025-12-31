#pragma once

#include "../../BaseClass/TransformComponent.h"
#include "../../Renderer/2DRenderer/Renderer2DComponent.h"
#include "../../../Physics/PhysicsWorldManager.h"
#include "../../../Managers/Camera/CameraManager.h"

#include <type_traits>

template<class AimRendererComponent, class GrapplingHookRendererComponent>
class GrapplingHookComponent : public TransformComponent
{
	static_assert(std::is_base_of<Renderer2DComponent, AimRendererComponent>::value, "AimRendererComponent class must derive from Renderer2DComponent");
	static_assert(std::is_base_of<Renderer2DComponent, GrapplingHookRendererComponent>::value, "GrapplingHookRendererComponent class must derive from Renderer2DComponent");

public:
	GrapplingHookComponent(std::shared_ptr<Actor> InOwner, const char* InAimTexturePath, const Vector2& InAimRendererSize = { 1.0f, 1.0f }, float InAimSpeed = 1.0f, float InAttractSpeed = 25.0f, float InMinGrapplingDistance = 10.0f, float InMaxGrapplingDistance = 200.0f, bool bAutoActivate = true, const Vector3 & InLocation = { 0.0f }, const Quaternion & InRotation = { 0.0f }, const Vector3 & InScale = { 1.0f, 1.0f, 1.0f });
	
	void UpdateAimPosition(const Vector2& InScale);
	void TriggerAttractGrapplingHook();
	void TriggerBalanceGrapplingHook();
	bool ClearBalanceGrapplingHook();

protected:
	virtual void Update(float DeltaTime) override;
	virtual void DrawDebug(float DeltaTime) override;

private:
	std::shared_ptr<AimRendererComponent> AimRendererComp;
	float AimSpeed;

	float AttractSpeed;

	bool bIsHookActivated;
	RaycastResult HookAttachedRaycastResult;
	Vector3 EndHookLocation { 0.0f };
	float CurrentEndHookAlpha { 0.0f };

	bool bAttractGrapplingHookTriggered = false;
	bool bBalanceGrapplingHookTriggered = false;

	void* CurrentAttachedJoint = nullptr;

	float MinGrapplingHookDistance;
	float MaxGrapplingHookDistance;

	std::shared_ptr<GrapplingHookRendererComponent> CableRendererComp;

	std::shared_ptr<MovementComponent> OwnerMovementComp;

	Vector2 MovingDirection { 0.0f };

	bool CanUseGrapplingHook() const;

	void UpdateAimRendererLocation(float DeltaTime);
	void UpdateGrapplingHookRenderer(float DeltaTime);
	void UpdateGrapplingHookAttached();

	void Attract();
	void Balance();

	DelegateBase<void, EMovementMode, EMovementMode>* OnMovementModeSwitchToGroundDelegate;
	void OnMovementModeSwitchToGround(EMovementMode PreviousMovementMode, EMovementMode CurrentMovementMode);
};

// Template function implementation must be in header

template<class AimRendererComponent, class GrapplingHookRendererComponent>
inline GrapplingHookComponent<AimRendererComponent, GrapplingHookRendererComponent>::GrapplingHookComponent(std::shared_ptr<Actor> InOwner, 
	const char* InAimTexturePath, const Vector2& InAimRendererSize, float InAimSpeed, float InAttractSpeed, 
	float InMinGrapplingDistance, float InMaxGrapplingDistance,bool bAutoActivate, 
const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale)
	: TransformComponent(InOwner, bAutoActivate, InLocation, InRotation, InScale), AimSpeed {InAimSpeed}, AttractSpeed {InAttractSpeed},
	bIsHookActivated{false}, MinGrapplingHookDistance {InMinGrapplingDistance}, MaxGrapplingHookDistance{InMaxGrapplingDistance}
{
	AimRendererComp = std::make_shared<AimRendererComponent>(InOwner, InAimTexturePath, true, InLocation, InRotation, InScale, InAimRendererSize);
	CableRendererComp = std::make_shared<GrapplingHookRendererComponent>(InOwner, "", true, false, InLocation, InRotation, InScale);
	if (InOwner) 
	{
		InOwner->AddComponent(AimRendererComp);
		InOwner->AddComponent(CableRendererComp);
		OwnerMovementComp = InOwner->GetComponentByClass<MovementComponent>();
	}
}

template<class AimRendererComponent, class GrapplingHookRendererComponent>
inline void GrapplingHookComponent<AimRendererComponent, GrapplingHookRendererComponent>::UpdateAimPosition(const Vector2& InScale)
{
	MovingDirection = InScale;
}

template<class AimRendererComponent, class GrapplingHookRendererComponent>
inline bool GrapplingHookComponent<AimRendererComponent, GrapplingHookRendererComponent>::CanUseGrapplingHook() const
{
	Vector3 WorldLocation = GetWorldLocation();
	Vector3 AimRendererWorldLocation = AimRendererComp->GetWorldLocation();
	return !bIsHookActivated && Vector3Distance(WorldLocation, AimRendererWorldLocation) >= MinGrapplingHookDistance && CurrentAttachedJoint == nullptr;
}

template<class AimRendererComponent, class GrapplingHookRendererComponent>
inline void GrapplingHookComponent<AimRendererComponent, GrapplingHookRendererComponent>::TriggerAttractGrapplingHook()
{
	if (!CanUseGrapplingHook())
		return;

	UpdateGrapplingHookAttached();
	bAttractGrapplingHookTriggered = true;
	bBalanceGrapplingHookTriggered = false;
}

template<class AimRendererComponent, class GrapplingHookRendererComponent>
inline bool GrapplingHookComponent<AimRendererComponent, GrapplingHookRendererComponent>::ClearBalanceGrapplingHook()
{
	if (CurrentAttachedJoint != nullptr)
	{
		PhysicsWorldManager::Get()->DestroyJoint(CurrentAttachedJoint);
		CurrentAttachedJoint = nullptr;
		bAttractGrapplingHookTriggered = false;
		bBalanceGrapplingHookTriggered = false;
		bIsHookActivated = false;
		CableRendererComp->Deactivate();

		return true;
	}

	return false;
}

template<class AimRendererComponent, class GrapplingHookRendererComponent>
inline void GrapplingHookComponent<AimRendererComponent, GrapplingHookRendererComponent>::TriggerBalanceGrapplingHook()
{
	if (ClearBalanceGrapplingHook() || !CanUseGrapplingHook())
	{
		if (OwnerMovementComp)
			OwnerMovementComp->SwitchMovementMode(EMovementMode::FALLING);
		return;
	}

	UpdateGrapplingHookAttached();
	bAttractGrapplingHookTriggered = false;
	bBalanceGrapplingHookTriggered = true;
}

template<class AimRendererComponent, class GrapplingHookRendererComponent>
inline void GrapplingHookComponent<AimRendererComponent, GrapplingHookRendererComponent>::UpdateGrapplingHookAttached()
{
	Vector3 WorldLocation = GetWorldLocation();
	Vector3 AimRendererWorldLocation = AimRendererComp->GetWorldLocation();
	Vector3 AimDirection = Vector3Subtract(AimRendererWorldLocation, WorldLocation);
	AimDirection = Vector3Normalize(AimDirection);
	EndHookLocation = Vector3Add(Vector3Scale(AimDirection, MaxGrapplingHookDistance), WorldLocation);

	bIsHookActivated = true;

	// Raycast to get end hook location
	HookAttachedRaycastResult = PhysicsWorldManager::Get()->Raycast(WorldLocation, EndHookLocation);
	if (HookAttachedRaycastResult.bHasHit)
	{
		EndHookLocation = HookAttachedRaycastResult.HitLocation;
	}

	CurrentEndHookAlpha = 0.0f;
	CableRendererComp->SetEndPosition(Vector::Vector3ToVector2(GetWorldLocation()));
	CableRendererComp->Activate();
}

template<class AimRendererComponent, class GrapplingHookRendererComponent>
inline void GrapplingHookComponent<AimRendererComponent, GrapplingHookRendererComponent>::Update(float DeltaTime)
{
	TransformComponent::Update(DeltaTime);

	UpdateAimRendererLocation(DeltaTime);

	UpdateGrapplingHookRenderer(DeltaTime);
}

template<class AimRendererComponent, class GrapplingHookRendererComponent>
inline void GrapplingHookComponent<AimRendererComponent, GrapplingHookRendererComponent>::DrawDebug(float DeltaTime)
{
	DrawCircle(EndHookLocation.x, EndHookLocation.y, 2.0f, BLUE);
}

template<class AimRendererComponent, class GrapplingHookRendererComponent>
inline void GrapplingHookComponent<AimRendererComponent, GrapplingHookRendererComponent>::UpdateAimRendererLocation(float DeltaTime)
{
	if (InputManager::Get()->GetIsInGamepadMode())
	{
		Vector2 ScaledSpeed = Vector2Scale(MovingDirection, AimSpeed * DeltaTime);
		Vector3 NewLocation = Vector3Add(AimRendererComp->GetComponentLocation(), Vector::Vector2ToVector3(ScaledSpeed));
		AimRendererComp->SetComponentLocation(NewLocation);
	}
	else
	{
		Vector3 NewLocation = Vector::Vector2ToVector3(GetScreenToWorld2D(MovingDirection, CameraManager::Get()->GetCameraToUse()));
		AimRendererComp->SetWorldLocation(NewLocation);
	}
	
}

template<class AimRendererComponent, class GrapplingHookRendererComponent>
inline void GrapplingHookComponent<AimRendererComponent, GrapplingHookRendererComponent>::Attract()
{
	if (OwnerMovementComp)
	{
		OwnerMovementComp->SwitchMovementMode(EMovementMode::GRAPPLING_THROWN);
		OnMovementModeSwitchToGroundDelegate =
			OwnerMovementComp->BindToOnMovementModeSwitch<
			GrapplingHookComponent<AimRendererComponent, GrapplingHookRendererComponent>,
			&GrapplingHookComponent<AimRendererComponent, GrapplingHookRendererComponent>::OnMovementModeSwitchToGround
			>(this);
	}

	if (std::shared_ptr<PhysicsComponent> OwnerPhysicsComp = GetOwner()->GetComponentByClass<PhysicsComponent>())
	{
		Vector3 Direction = Vector3Subtract(EndHookLocation, GetOwner()->GetActorLocation());
		Direction = Vector3Normalize(Direction);
		OwnerPhysicsComp->SetLinearVelocity(Vector3Scale(Direction, AttractSpeed));
	}
}

template<class AimRendererComponent, class GrapplingHookRendererComponent>
inline void GrapplingHookComponent<AimRendererComponent, GrapplingHookRendererComponent>::Balance()
{
	if (HookAttachedRaycastResult.bHasHit)
	{
		if (OwnerMovementComp)
		{
			if (!OwnerMovementComp->SwitchMovementMode(EMovementMode::GRAPPLING_BALANCE))
			{
				CableRendererComp->Deactivate();
				return;
			}
		}

		CurrentAttachedJoint = PhysicsWorldManager::Get()->CreateDistanceJointBetween(GetOwner()->GetComponentByClass<PhysicsComponent>(),
			HookAttachedRaycastResult.HitActor->GetComponentByClass<PhysicsComponent>(),
			GetWorldLocation(), HookAttachedRaycastResult.HitLocation);
	}
	else
	{
		CableRendererComp->Deactivate();
	}
}

template<class AimRendererComponent, class GrapplingHookRendererComponent>
inline void GrapplingHookComponent<AimRendererComponent, GrapplingHookRendererComponent>::UpdateGrapplingHookRenderer(float DeltaTime)
{
	if (bIsHookActivated)
	{
		CurrentEndHookAlpha += DeltaTime * 5.0f;
		if (CurrentEndHookAlpha >= 1.0f)
		{
			CurrentEndHookAlpha = 1.0f;
			bIsHookActivated = false;

			if (bAttractGrapplingHookTriggered)
			{
				Attract();
			}
			else if (bBalanceGrapplingHookTriggered)
			{
				Balance();
			}

			bAttractGrapplingHookTriggered = false;
			bBalanceGrapplingHookTriggered = false;
		}

		Vector3 CurrentEndHookLocation = Vector3Lerp(GetWorldLocation(), EndHookLocation, CurrentEndHookAlpha);
		CableRendererComp->SetEndPosition(Vector::Vector3ToVector2(CurrentEndHookLocation));
	}
}

template<class AimRendererComponent, class GrapplingHookRendererComponent>
inline void GrapplingHookComponent<AimRendererComponent, GrapplingHookRendererComponent>::OnMovementModeSwitchToGround(EMovementMode PreviousMovementMode, EMovementMode CurrentMovementMode)
{
	CableRendererComp->Deactivate();
	std::shared_ptr<MovementComponent> OwnerMovementComp = GetOwner()->GetComponentByClass<MovementComponent>();
	if (OwnerMovementComp)
	{
		OwnerMovementComp->UnbindToOnMovementModeSwitch(OnMovementModeSwitchToGroundDelegate);
	}
}