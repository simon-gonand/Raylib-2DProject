#include "MultipleChildrenWidget.h"
#include <raymath.h>

MultipleChildrenWidget::MultipleChildrenWidget(const Vector2& InPosition, float InRotation, const Vector2& InScale, float InOpacity)
	: Widget(InPosition, InRotation, InScale, InOpacity)
{
}

void MultipleChildrenWidget::AddChild(std::shared_ptr<Widget> InChild)
{
	if (!InChild)
		return;
	
	Children.push_back(InChild);
}

void MultipleChildrenWidget::RemoveChild(std::shared_ptr<Widget> InChild)
{
	std::vector<std::shared_ptr<Widget>>::iterator ChildToRemove = std::find(Children.begin(), Children.end(), InChild);
	if (ChildToRemove == Children.end())
		return;

	Children.erase(ChildToRemove);
}

void MultipleChildrenWidget::Update(float DeltaTime, const Vector2& ParentPosition, const float& ParentRotation, const Vector2& ParentScale, const float& ParentOpacity)
{
	for (std::shared_ptr<Widget> Child : Children)
	{
		if (Child)
			Child->Update(DeltaTime, GetWorldPosition(ParentPosition), GetWorldRotation(ParentRotation), GetWorldScale(ParentScale), GetWorldOpacity(ParentOpacity));
	}
}

Vector2 MultipleChildrenWidget::GetSize(const Vector2& ParentScale) const
{
	Vector2 Result = Vector2Zero();
	Vector2 WorldScale = GetWorldScale(ParentScale);
	for (std::shared_ptr<Widget> Child : Children)
	{
		Vector2 ChildSize = Child->GetSize(WorldScale);
		Result.x = ChildSize.x > Result.x ? ChildSize.x : Result.x;
		Result.y = ChildSize.y > Result.y ? ChildSize.y : Result.y;
	}
	return Result;
}
