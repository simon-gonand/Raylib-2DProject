#pragma once

#include "../RendererComponent.h"

class Renderer2DComponent : public RendererComponent
{
public:
	Renderer2DComponent(std::shared_ptr<Actor> Owner, const char* TexturePath, bool bAutoActivate = true, const Vector3& InLocation = { 0.0f }, const Quaternion& InRotation = { 0.0f }, const Vector3& InScale = { 1.0f, 1.0f, 1.0f }, const Vector2& InSize = { 1.0f, 1.0f }, std::shared_ptr<AnimationManager> InAnimManager = nullptr);

protected:
	Texture2D DefaultTexture2D;

	Vector2 Size;

	bool bIsDrawnInverted = false;

	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;

	Vector2 GetSizeScaledWithRatio() const;

private:
	const char* DefaultTexturePath;
};