#pragma once

#include "../Renderer2DComponent.h"
#include "../../../../Animations/2D/SpriteSheet2DAnimation.h"

class SpriteSheet2DRendererComponent : public Renderer2DComponent
{
public:
	SpriteSheet2DRendererComponent(std::shared_ptr<Actor> Owner, const char* DefaultTexturePath, const Vector3& InLocation = { 0.0f }, const Quaternion& InRotation = { 0.0f }, const Vector3& InScale = { 1.0f, 1.0f, 1.0f }, const Vector2& InSize = { 1.0f, 1.0f }, std::shared_ptr<AnimationManager> InAnimManager = nullptr);

protected:
	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;
};