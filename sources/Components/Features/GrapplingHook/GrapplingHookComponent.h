#pragma once

#include "../../BaseClass/TransformComponent.h"
#include "../../Renderer/2DRenderer/Renderer2DComponent.h"

#include <type_traits>

template<class AimRendererComponent, class GrapplingHookRendererComponent>
class GrapplingHookComponent : public TransformComponent
{
	static_assert(std::is_base_of<Renderer2DComponent, AimRendererComponent>::value, "AimRendererComponent class must derive from Renderer2DComponent");
	static_assert(std::is_base_of<Renderer2DComponent, GrapplingHookRendererComponent>::value, "GrapplingHookRendererComponent class must derive from Renderer2DComponent");

public:
	GrapplingHookComponent(std::shared_ptr<Actor> InOwner, const char* InAimTexturePath, const Vector2& InAimRendererSize = { 1.0f, 1.0f }, float InAimSpeed = 1.0f, const Vector3 & InLocation = { 0.0f }, const Quaternion & InRotation = { 0.0f }, const Vector3 & InScale = { 1.0f, 1.0f, 1.0f });
	
	void UpdateAimPosition(const Vector2& InScale);

protected:
	virtual void Update(float DeltaTime) override;

private:
	std::shared_ptr<AimRendererComponent> AimRendererComp;
	float AimSpeed;

	std::shared_ptr<GrapplingHookRendererComponent> CableRendererComp;

	Vector2 MovingDirection;
};

// Template function implementation must be in header

template<class AimRendererComponent, class GrapplingHookRendererComponent>
inline GrapplingHookComponent<AimRendererComponent, GrapplingHookRendererComponent>::GrapplingHookComponent(std::shared_ptr<Actor> InOwner, const char* InAimTexturePath, const Vector2& InAimRendererSize, float InAimSpeed, const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale)
	: TransformComponent(InOwner, InLocation, InRotation, InScale), AimSpeed {InAimSpeed}
{
	AimRendererComp = std::make_shared<AimRendererComponent>(InOwner, InAimTexturePath, InLocation, InRotation, InScale, InAimRendererSize);
	CableRendererComp = std::make_shared<GrapplingHookRendererComponent>(InOwner, "", true, InLocation, InRotation, InScale);
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
inline void GrapplingHookComponent<AimRendererComponent, GrapplingHookRendererComponent>::Update(float DeltaTime)
{
	Vector2 ScaledSpeed = Vector2Scale(MovingDirection, AimSpeed * DeltaTime);
	Vector3 NewLocation = Vector3Add(AimRendererComp->GetComponentLocation(), Vector::Vector2ToVector3(ScaledSpeed));
	AimRendererComp->SetComponentLocation(NewLocation);
}
