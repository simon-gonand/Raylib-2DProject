#pragma once

#include <raylib.h>

class Widget
{
public:
	Widget(const Vector2& InPosition = { 0.0f }, float InRotation = 0.0f, const Vector2& InScale = { 1.0f, 1.0f }, float InOpacity = 1.0f);

	virtual void Update(float DeltaTime, const Vector2& ParentPosition, const float& ParentRotation, const Vector2& ParentScale, const float& ParentOpacity) = 0;

	virtual Vector2 GetSize(const Vector2& ParentScale) const = 0;

protected:
	Vector2 Position;
	float Rotation;
	Vector2 Scale;

	float Opacity;

	Vector2 GetWorldPosition(const Vector2& ParentPosition) const;
	float GetWorldRotation(const float& ParentRotation) const;
	Vector2 GetWorldScale(const Vector2& ParentScale) const;
	float GetWorldOpacity(const float& ParentOpacity) const;

	Color GetDrawColorOpacity(const Color& InColor, const float& InOpacity) const;

};

