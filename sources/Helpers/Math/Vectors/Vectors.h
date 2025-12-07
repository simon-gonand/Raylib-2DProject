#pragma once

#include<string>
#include <raylib.h>


namespace Vector 
{
	// UP and DOWN vectors are inverted because 0,0 origin of screen is at the top left
	inline const Vector3& UpVector = {0.0f, -1.0f, 0.0f};
	inline const Vector3& DownVector = { 0.0f, 1.0f, 0.0f };
	inline const Vector3& RightVector = { 1.0f, 0.0f, 0.0f };
	inline const Vector3& LeftVector = { -1.0f, 0.0f, 0.0f };
	
	// UP nd DOWN vectors are inverted because 0,0 origin of screen is at the top left
	inline const Vector2& UpVector2 = { 0.0f, -1.0f};
	inline const Vector2& DownVector2 = { 0.0f, 1.0f};
	inline const Vector2& RightVector2 = { 1.0f, 0.0f};
	inline const Vector2& LeftVector2 = { -1.0f, 0.0f};

	Vector2 Vector3ToVector2(Vector3 Vector);
	Vector2 OppositeVector2(Vector2 Vector);
}