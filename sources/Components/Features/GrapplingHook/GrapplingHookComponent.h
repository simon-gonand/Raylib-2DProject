#pragma once

#include "../../BaseClass/TransformComponent.h"
#include "../../Renderer/2DRenderer/Renderer2DComponent.h"

#include <type_traits>

template<class AimRendererComponent>
class GrapplingHookComponent : public TransformComponent
{
	static_assert(std::is_base_of<AimRendererComponent, Renderer2DComponent>::value, "AimRendererComponent class must derive from Renderer2DComponent");

public:
	GrapplingHookComponent(std::shared_ptr<Actor> InOwner, const char* AimTexturePath, const Vector2& AimRendererSize = { 1.0f, 1.0f }, const Vector3 & InLocation = { 0.0f }, const Quaternion & InRotation = { 0.0f }, const Vector3 & InScale = { 1.0f, 1.0f, 1.0f });
	virtual void Update(float DeltaTime) override;

private:
	std::shared_ptr<AimRendererComponent> AimRendererComp;
};

// Template function implementation must be in header

template<class AimRendererComponent>
inline GrapplingHookComponent<AimRendererComponent>::GrapplingHookComponent(std::shared_ptr<Actor> InOwner, const char* AimTexturePath, const Vector2& AimRendererSize, const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale)
	: TransformComponent(InOwner, InLocation, InRotation, InScale)
{
	AimRendererComp = std::make_shared<AimRendererComponent>(InOwner, AimTexturePath, InLocation, InRotation, InScale, AimRendererSize);
	if (InOwner) 
	{
		InOwner->AddComponent(AimRendererComp);
	}
}

template<class AimRendererComponent>
inline void GrapplingHookComponent<AimRendererComponent>::Update(float DeltaTime)
{
}
