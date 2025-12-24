#pragma once

#include "../../BaseClass/TransformComponent.h"
#include "../../Renderer/2DRenderer/Renderer2DComponent.h"
#include "../../../Physics/PhysicsWorldManager.h"

#include <type_traits>

template<class AimRendererComponent, class GrapplingHookRendererComponent>
class GrapplingHookComponent : public TransformComponent
{
	static_assert(std::is_base_of<Renderer2DComponent, AimRendererComponent>::value, "AimRendererComponent class must derive from Renderer2DComponent");
	static_assert(std::is_base_of<Renderer2DComponent, GrapplingHookRendererComponent>::value, "GrapplingHookRendererComponent class must derive from Renderer2DComponent");

public:
	GrapplingHookComponent(std::shared_ptr<Actor> InOwner, const char* InAimTexturePath, const Vector2& InAimRendererSize = { 1.0f, 1.0f }, float InAimSpeed = 1.0f, bool bAutoActivate = true, const Vector3 & InLocation = { 0.0f }, const Quaternion & InRotation = { 0.0f }, const Vector3 & InScale = { 1.0f, 1.0f, 1.0f });
	
	void UpdateAimPosition(const Vector2& InScale);
	void TriggerGrapplingHook();

protected:
	virtual void Update(float DeltaTime) override;
	virtual void DrawDebug(float DeltaTime) override;

private:
	std::shared_ptr<AimRendererComponent> AimRendererComp;
	float AimSpeed;

	bool bIsHookActivated;
	Vector3 EndHookLocation { 0.0f };
	float CurrentEndHookAlpha { 0.0f };

	std::shared_ptr<GrapplingHookRendererComponent> CableRendererComp;

	Vector2 MovingDirection { 0.0f };

	void UpdateAimRendererLocation(float DeltaTime);
	void UpdateGrapplingHookRenderer(float DeltaTime);
};

// Template function implementation must be in header

template<class AimRendererComponent, class GrapplingHookRendererComponent>
inline GrapplingHookComponent<AimRendererComponent, GrapplingHookRendererComponent>::GrapplingHookComponent(std::shared_ptr<Actor> InOwner, const char* InAimTexturePath, const Vector2& InAimRendererSize, float InAimSpeed, bool bAutoActivate, const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale)
	: TransformComponent(InOwner, bAutoActivate, InLocation, InRotation, InScale), AimSpeed {InAimSpeed}, bIsHookActivated{false}
{
	AimRendererComp = std::make_shared<AimRendererComponent>(InOwner, InAimTexturePath, true, InLocation, InRotation, InScale, InAimRendererSize);
	CableRendererComp = std::make_shared<GrapplingHookRendererComponent>(InOwner, "", true, false, InLocation, InRotation, InScale);
	if (InOwner) 
	{
		InOwner->AddComponent(AimRendererComp);
		InOwner->AddComponent(CableRendererComp);
	}
}

template<class AimRendererComponent, class GrapplingHookRendererComponent>
inline void GrapplingHookComponent<AimRendererComponent, GrapplingHookRendererComponent>::UpdateAimPosition(const Vector2& InScale)
{
	MovingDirection = InScale;
}

template<class AimRendererComponent, class GrapplingHookRendererComponent>
inline void GrapplingHookComponent<AimRendererComponent, GrapplingHookRendererComponent>::TriggerGrapplingHook()
{
	if (bIsHookActivated)
		return;

	bIsHookActivated = true;

	// Raycast to get end hook location
	RaycastResult Result = PhysicsWorldManager::Get()->Raycast(GetWorldLocation(), AimRendererComp->GetWorldLocation());
	if (Result.bHasHit)
	{
		EndHookLocation = Result.HitLocation;
	}
	else
	{
		EndHookLocation = AimRendererComp->GetWorldLocation();
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
	Vector2 ScaledSpeed = Vector2Scale(MovingDirection, AimSpeed * DeltaTime);
	Vector3 NewLocation = Vector3Add(AimRendererComp->GetComponentLocation(), Vector::Vector2ToVector3(ScaledSpeed));
	AimRendererComp->SetComponentLocation(NewLocation);
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

			// Attract Owner
			std::shared_ptr<MovementComponent> OwnerMovementComp = GetOwner()->GetComponentByClass<MovementComponent>();
			if (OwnerMovementComp)
			{
				OwnerMovementComp->SwitchMovementMode(EMovementMode::GRAPPLING_THROWN);
			}

			if (std::shared_ptr<PhysicsComponent> OwnerPhysicsComp = GetOwner()->GetComponentByClass<PhysicsComponent>())
			{
				Vector3 Direction = Vector3Subtract(EndHookLocation, GetOwner()->GetActorLocation());
				Direction = Vector3Normalize(Direction);
				OwnerPhysicsComp->ApplyForce(Vector3Scale(Direction, 7500.0f));
			}
		}
		Vector3 CurrentEndHookLocation = Vector3Lerp(GetWorldLocation(), EndHookLocation, CurrentEndHookAlpha);
		CableRendererComp->SetEndPosition(Vector::Vector3ToVector2(CurrentEndHookLocation));
	}
}
