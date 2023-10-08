#include "Transform2D.h"

#include<raymath.h>


void Transform2D::UpdateDrawLocation()
{
	MyVector2 ScaledRotation = Location * Scale;
	DrawLocation = Vector2Rotate(ScaledRotation, Rotation);
}

Transform2D::Transform2D()
{
	UpdateDrawLocation();
}

Transform2D::Transform2D(const Transform2D& CopyRef)
{
	Location = CopyRef.GetLocation();
	Rotation = CopyRef.GetRotation();
	Scale = CopyRef.GetScale();
	UpdateDrawLocation();
}

Transform2D::Transform2D(const Transform2D&& MoveRef) noexcept
{
	Location = MoveRef.GetLocation();
	Rotation = MoveRef.GetRotation();
	Scale = MoveRef.GetScale();
	UpdateDrawLocation();
}

const MyVector2& Transform2D::GetLocation() const
{
	return Location;
}

const float& Transform2D::GetRotation() const
{
	return Rotation;
}

const MyVector2& Transform2D::GetScale() const
{
	return Scale;
}

const MyVector2& Transform2D::GetDrawLocation() const
{
	return DrawLocation;
}

void Transform2D::SetLocation(const MyVector2& NewLocation)
{
	Location = NewLocation;
	UpdateDrawLocation();
}

void Transform2D::AddLocation(const MyVector2& AddLocation)
{
	Location += AddLocation;
	UpdateDrawLocation();
}

void Transform2D::SetRotation(const float& NewRotation)
{
	Rotation = NewRotation;
	UpdateDrawLocation();
}

void Transform2D::SetScale(const MyVector2& NewScale)
{
	Scale = NewScale;
	UpdateDrawLocation();
}
