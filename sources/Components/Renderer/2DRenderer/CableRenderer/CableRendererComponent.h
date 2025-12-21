#pragma once

#include "../Renderer2DComponent.h"

class CableRendererComponent : public Renderer2DComponent
{
public:
	CableRendererComponent(std::shared_ptr<Actor> InOwner, const char* TexturePath, bool bInUseComponentLocationAsStartPosition, const Vector3& InLocation = {0.0f}, const Quaternion& InRotation = {0.0f}, const Vector3& InScale = {1.0f, 1.0f, 1.0f}, const Vector2& InSize = {1.0f, 1.0f}, std::shared_ptr<AnimationManager> InAnimManager = nullptr);
	
	void SetStartPosition(const Vector2& InStartPosition);
	void SetEndPosition(const Vector2& InEndPosition);
protected:
	virtual void Update(float DeltaTime) override;

private:
	Vector2 StartPosition;
	Vector2 EndPosition;

	bool bUseComponentLocationAsStartPosition;
};