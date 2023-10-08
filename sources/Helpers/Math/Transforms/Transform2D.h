#pragma once
#include "../Vectors/Vectors.h"

class Transform2D
{
private:
	MyVector2 Location = { 0.0f, 0.0f };
	float Rotation = 0.0f;
	MyVector2 Scale = { 1.0f, 1.0f };

	MyVector2 DrawLocation;

	void UpdateDrawLocation(); // Apply Translation, Scale and Rotation to a point to know where to draw it

public:
	Transform2D();
	Transform2D(const Transform2D& CopyRef);
	Transform2D(const Transform2D&& MoveRef) noexcept;

	const MyVector2& GetLocation() const;
	const float& GetRotation() const;
	const MyVector2& GetScale() const;

	const MyVector2& GetDrawLocation() const;

	void SetLocation(const MyVector2& NewLocation);
	void AddLocation(const MyVector2& AddedLocation);
	void SetRotation(const float& Angle);
	void SetScale(const MyVector2& NewScale);
};

