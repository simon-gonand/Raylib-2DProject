#pragma once

#include <raylib.h>
#include <raymath.h>

namespace Math
{
	float FloatInterpTo(const float& Current, const float& Target, float DeltaTime, float InterpSpeed);
	Vector3 Vector3InterpTo(const Vector3& Current, const Vector3& Target, float DeltaTime, float InterpSpeed);
	Vector2 Vector2InterpTo(const Vector2& Current, const Vector2& Target, float DeltaTime, float InterpSpeed);
}