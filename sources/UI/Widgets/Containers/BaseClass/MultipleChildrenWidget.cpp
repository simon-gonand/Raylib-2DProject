#include "MultipleChildrenWidget.h"

#include "Slot.h"

#include <raymath.h>

MultipleChildrenWidget::MultipleChildrenWidget(const Vector2& InPosition, float InRotation, const Vector2& InScale, float InOpacity, const Vector4& InChildrenPadding)
	: Widget(InPosition, InRotation, InScale, InOpacity), ChildrenPadding{ InChildrenPadding }
{
}

void MultipleChildrenWidget::AddChild(std::shared_ptr<Widget> InChild)
{
	if (!InChild)
		return;
	
	std::shared_ptr<Slot> ChildSlot = std::make_shared<Slot>(ChildrenPadding);
	ChildSlot->SetWidgetRef(InChild);
	ChildSlots.push_back(ChildSlot);
}

void MultipleChildrenWidget::RemoveChild(std::shared_ptr<Widget> InChild)
{
	std::vector<std::shared_ptr<Slot>>::iterator ChildToRemove = std::find_if(ChildSlots.begin(), ChildSlots.end(),
		[InChild](const std::shared_ptr<Slot> ChildSlot)
		{
			return InChild == ChildSlot->GetWidgetRef();
		});

	if (ChildToRemove == ChildSlots.end())
		return;

	ChildSlots.erase(ChildToRemove);
}

std::shared_ptr<Widget> MultipleChildrenWidget::GetChildAt(int Index)
{
	if (Index < 0 || Index >= ChildSlots.size())
		return nullptr;

	std::shared_ptr<Slot> Child = ChildSlots[Index];
	if (Child)
		return Child->GetWidgetRef();

	return nullptr;
}

void MultipleChildrenWidget::Update(float DeltaTime, const Vector2& ParentPosition, const float& ParentRotation, const Vector2& ParentScale, const float& ParentOpacity)
{
	for (std::shared_ptr<Slot> Child : ChildSlots)
	{
		if (Child)
			Child->Update(DeltaTime, GetWorldPosition(ParentPosition), GetWorldRotation(ParentRotation), GetWorldScale(ParentScale), GetWorldOpacity(ParentOpacity));
	}
}

Vector2 MultipleChildrenWidget::GetSize(const Vector2& ParentScale) const
{
	Vector2 Result = Vector2Zero();
	Vector2 WorldScale = GetWorldScale(ParentScale);
	for (std::shared_ptr<Slot> Child : ChildSlots)
	{
		Vector2 ChildSize = Child->GetSize(WorldScale);
		Result.x = ChildSize.x > Result.x ? ChildSize.x : Result.x;
		Result.y = ChildSize.y > Result.y ? ChildSize.y : Result.y;
	}
	return Result;
}
