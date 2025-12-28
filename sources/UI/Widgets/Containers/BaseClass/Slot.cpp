#include "Slot.h"
#include <raymath.h>

Slot::Slot(Vector4 InPadding)
	: WidgetRef{nullptr}, Padding{InPadding}
{
}

void Slot::Update(float DeltaTime, const Vector2& ParentPosition, const float& ParentRotation, const Vector2& ParentScale, const float& ParentOpacity)
{
	if (WidgetRef)
	{
		Vector2 Position = UpdatePosition(ParentPosition);
		WidgetRef->Update(DeltaTime, Position, ParentRotation, ParentScale, ParentOpacity);
	}
}

void Slot::SetPadding(const Vector4& InPadding)
{
	Padding = InPadding;
}

void Slot::SetWidgetRef(std::shared_ptr<Widget> InWidgetRef)
{
	WidgetRef = InWidgetRef;
}

Vector2 Slot::UpdateSize(const Vector2& InWidgetSize) const
{
	return {InWidgetSize.x + Padding.x + Padding.z, InWidgetSize.y + Padding.y + Padding.w};
}

Vector2 Slot::GetSize(const Vector2& ParentScale) const
{
	if (!WidgetRef)
		return Vector2Zero();

	return UpdateSize(WidgetRef->GetSize(ParentScale));
}

const std::shared_ptr<Widget> Slot::GetWidgetRef() const
{
	return WidgetRef;
}

Vector2 Slot::UpdatePosition(const Vector2& Position) const
{
	return { Position.x + Padding.x, Position.y + Padding.y };
}
