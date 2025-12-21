#pragma once

#include "../../BaseClass/TransformComponent.h"
#include "../../Renderer/2DRenderer/Renderer2DComponent.h"

#include <type_traits>

template<class AimRendererComponent>
class GrapplingHookComponent : public TransformComponent
{
	static_assert(std::is_base_of<AimRendererComponent, Renderer2DComponent>::value, "AimRendererComponent class must derive from Renderer2DComponent");

public:
	GrapplingHookComponent(std::shared_ptr<Actor> InOwner, const char* InAimTexturePath, const Vector2& InAimRendererSize = { 1.0f, 1.0f }, float InAimSpeed = 1.0f, const Vector3 & InLocation = { 0.0f }, const Quaternion & InRotation = { 0.0f }, const Vector3 & InScale = { 1.0f, 1.0f, 1.0f });
	
	void UpdateAimPosition(const Vector2& InScale);

protected:
	virtual void Update(float DeltaTime) override;

private:
	std::shared_ptr<AimRendererComponent> AimRendererComp;
	float AimSpeed;
};

// Template function implementation must be in header

template<class AimRendererComponent>
inline GrapplingHookComponent<AimRendererComponent>::GrapplingHookComponent(std::shared_ptr<Actor> InOwner, const char* InAimTexturePath, const Vector2& InAimRendererSize, float InAimSpeed, const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale)
	: TransformComponent(InOwner, InLocation, InRotation, InScale), AimSpeed {InAimSpeed}
{
	AimRendererComp = std::make_shared<AimRendererComponent>(InOwner, InAimTexturePath, InLocation, InRotation, InScale, InAimRendererSize);
	if (InOwner) 
	{
		InOwner->AddComponent(AimRendererComp);
	}
}

template<class AimRendererComponent>
inline void GrapplingHookComponent<AimRendererComponent>::UpdateAimPosition(const Vector2& InScale)
{
	Vector2 ScaledSpeed = Vector2Scale(InScale, AimSpeed);
	Vector3 NewLocation = Vector3Add(AimRendererComp->GetComponentLocation(), Vector::Vector2ToVector3(ScaledSpeed));
	AimRendererComp->SetComponentLocation(NewLocation);
}

template<class AimRendererComponent>
inline void GrapplingHookComponent<AimRendererComponent>::Update(float DeltaTime)
{
}
