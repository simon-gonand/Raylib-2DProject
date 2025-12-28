#include "OneChildWidget.h"

#include "Slot.h"

OneChildWidget::OneChildWidget(const Vector2& InPosition, float InRotation, const Vector2& InScale, float InOpacity, const Vector4& ChildPadding, bool bInChildOverrideMinSize)
	: Widget(InPosition, InRotation, InScale, InOpacity), bChildOverrideMinSize {bInChildOverrideMinSize}
{
	ChildSlot = std::make_shared<Slot>(ChildPadding);
}

void OneChildWidget::SetChild(std::shared_ptr<Widget> InChild)
{
	if (!ChildSlot)
		return;

	ChildSlot->SetWidgetRef(InChild);
}

void OneChildWidget::Update(float DeltaTime, const Vector2& ParentPosition, const float& ParentRotation, const Vector2& ParentScale, const float& ParentOpacity)
{
	if (!ChildSlot)
		return;

	ChildSlot->Update(DeltaTime, GetWorldPosition(ParentPosition), GetWorldRotation(ParentRotation), GetWorldScale(ParentScale), GetWorldOpacity(ParentOpacity));
}

Vector2 OneChildWidget::GetSize(const Vector2& ParentScale) const
{
	Vector2 WorldScale = GetWorldScale(ParentScale);
	return ChildSlot->GetSize(WorldScale);
}
