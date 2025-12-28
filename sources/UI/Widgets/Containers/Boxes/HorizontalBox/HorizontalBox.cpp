#include "HorizontalBox.h"

#include "../../BaseClass/Slot.h"
#include <raymath.h>

HorizontalBox::HorizontalBox(const Vector2& InPosition, float InRotation, const Vector2& InScale, float InOpacity, const Vector4& InChildrenPadding)
	: MultipleChildrenWidget(InPosition, InRotation, InScale, InOpacity, InChildrenPadding)
{
}

void HorizontalBox::Update(float DeltaTime, const Vector2& ParentPosition, const float& ParentRotation, const Vector2& ParentScale, const float& ParentOpacity)
{
	float HorizontalOffset = 0.0f;
	for (std::shared_ptr<Slot> ChildSlot : ChildSlots)
	{
		Vector2 OffsetPosition = ParentPosition;
		OffsetPosition.x += HorizontalOffset;
		ChildSlot->Update(DeltaTime, OffsetPosition, ParentRotation, ParentScale, ParentOpacity);
		HorizontalOffset += ChildSlot->GetSize(ParentScale).x;
	}
}

Vector2 HorizontalBox::GetSize(const Vector2& ParentScale) const
{
	Vector2 Result = Vector2Zero();
	Vector2 WorldScale = GetWorldScale(ParentScale);
	for (std::shared_ptr<Slot> Child : ChildSlots)
	{
		Vector2 ChildSize = Child->GetSize(WorldScale);
		Result.x += ChildSize.x;
		Result.y = ChildSize.y > Result.y ? ChildSize.y : Result.y;
	}
	return Result;
}
