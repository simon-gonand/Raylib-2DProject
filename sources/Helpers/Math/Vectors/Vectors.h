#pragma once

#include<string>
#include <raylib.h>


struct MyVector2 : public Vector2
{
public:

	static const MyVector2& ZeroVector;
	static const MyVector2& UpVector;
	static const MyVector2& DownVector;
	static const MyVector2& RightVector;
	static const MyVector2& LeftVector;

	MyVector2(float X = 0.0f, float Y = 0.0f);
	MyVector2(const Vector2& Vector);
	MyVector2(const MyVector2& Vector);
	MyVector2(MyVector2&& Vector) noexcept;

	MyVector2 operator+(const MyVector2& Other);
	void operator =(const MyVector2& Other);
	void operator+=(const MyVector2& Other);

	MyVector2 operator*(const MyVector2& Other) const;
	MyVector2 operator*(const float& Other) const;
	MyVector2 operator*(const int& Other) const;

	float GetMagnitude() const;
	MyVector2 Normalize();

	std::string ToString() const;
};