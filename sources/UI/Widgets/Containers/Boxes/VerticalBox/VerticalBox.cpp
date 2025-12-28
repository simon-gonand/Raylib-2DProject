#include "VerticalBox.h"

#include "../../BaseClass/Slot.h"

#include <raymath.h>

VerticalBox::VerticalBox(const Vector2& InPosition, float InRotation, const Vector2& InScale, float InOpacity, const Vector4& InChildrenPadding)
	: MultipleChildrenWidget(InPosition, InRotation, InScale, InOpacity, InChildrenPadding)
{
}

void VerticalBox::Update(float DeltaTime, const Vector2& ParentPosition, const float& ParentRotation, const Vector2& ParentScale, const float& ParentOpacity)
{
	float VerticalOffset = 0.0f;
	for (std::shared_ptr<Slot> ChildSlot : ChildSlots)
	{
		Vector2 OffsetPosition = ParentPosition;
		OffsetPosition.y += VerticalOffset;
		ChildSlot->Update(DeltaTime, OffsetPosition, ParentRotation, ParentScale, ParentOpacity);
		VerticalOffset += ChildSlot->GetSize(ParentScale).y;
	}
}

Vector2 VerticalBox::GetSize(const Vector2& ParentScale) const
{
	Vector2 Result = Vector2Zero();
	Vector2 WorldScale = GetWorldScale(ParentScale);
	for (std::shared_ptr<Slot> Child : ChildSlots)
	{
		Vector2 ChildSize = Child->GetSize(WorldScale);
		Result.x = ChildSize.x > Result.x ? ChildSize.x : Result.x;
		Result.y += ChildSize.y;
	}
	return Result;
}
