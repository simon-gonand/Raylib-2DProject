#include "Vectors.h"

#include <math.h>

const MyVector2& MyVector2::ZeroVector = MyVector2();
const MyVector2& MyVector2::UpVector = MyVector2(0.0f, 1.0f);
const MyVector2& MyVector2::DownVector = MyVector2(0.0f, -1.0f);
const MyVector2& MyVector2::RightVector = MyVector2(1.0f, 0.0f);
const MyVector2& MyVector2::LeftVector = MyVector2(-1.0f, 0.0f);

MyVector2::MyVector2(float X, float Y)
{
	x = X;
	y = Y;
}

MyVector2::MyVector2(const MyVector2& Vector)
{
	x = Vector.x;
	y = Vector.y;
}

MyVector2::MyVector2(MyVector2&& Vector) noexcept
{
	x = Vector.x;
	y = Vector.y;
}


MyVector2 MyVector2::operator+(const MyVector2& Other)
{
	return MyVector2(x + Other.x, y + Other.y);
}

void MyVector2::operator=(const MyVector2& Other)
{
	x = Other.x;
	y = Other.y;
}

void MyVector2::operator+=(const MyVector2& Other)
{
	x += Other.x;
	y += Other.y;
}

MyVector2 MyVector2::operator*(const MyVector2& Other) const
{
	return MyVector2(x * Other.x, y * Other.y);
}

MyVector2 MyVector2::operator*(const float& Other) const
{
	return MyVector2(x * Other, y * Other);
}

MyVector2 MyVector2::operator*(const int& Other) const
{
	return MyVector2(x * Other, y * Other);
}

float MyVector2::GetMagnitude() const
{
	return sqrt((x * x) + (y * y));
}

void MyVector2::Normalize()
{
	float Magnitude = GetMagnitude();
	if (Magnitude == 0.0f) return;

	x /= Magnitude;
	y /= Magnitude;
}

std::string MyVector2::ToString() const
{
	return "{ " + std::to_string(x) + "; " + std::to_string(y) + " }";
}
