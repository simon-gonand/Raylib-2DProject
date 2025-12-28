#include "OneChildWidget.h"

OneChildWidget::OneChildWidget(const Vector2& InPosition, float InRotation, const Vector2& InScale, float InOpacity, bool bInChildOverrideMinSize)
	: Widget(InPosition, InRotation, InScale, InOpacity), bChildOverrideMinSize {bInChildOverrideMinSize}
{
}

void OneChildWidget::SetChild(std::shared_ptr<Widget> InChild)
{
	Child = InChild;
}

void OneChildWidget::Update(float DeltaTime, const Vector2& ParentPosition, const float& ParentRotation, const Vector2& ParentScale, const float& ParentOpacity)
{
	if (!Child)
		return;

	Child->Update(DeltaTime, GetWorldPosition(ParentPosition), GetWorldRotation(ParentRotation), GetWorldScale(ParentScale), GetWorldOpacity(ParentOpacity));
}

Vector2 OneChildWidget::GetSize(const Vector2& ParentScale) const
{
	Vector2 WorldScale = GetWorldScale(ParentScale);
	return Child->GetSize(WorldScale);
}
