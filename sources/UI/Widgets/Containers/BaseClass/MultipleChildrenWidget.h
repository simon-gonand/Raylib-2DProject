#pragma once

#include "../../BaseClass/Widget.h"

#include <memory>
#include <vector>

class MultipleChildrenWidget : public Widget
{
public:
	MultipleChildrenWidget(const Vector2& InPosition = { 0.0f }, float InRotation = 0.0f, const Vector2& InScale = { 1.0f, 1.0f }, float InOpacity = 1.0f, const Vector4& InChildrenPadding = {0.0f});

	virtual void AddChild(std::shared_ptr<Widget> InChild);
	void RemoveChild(std::shared_ptr<Widget> InChild);

protected:
	virtual void Update(float DeltaTime, const Vector2& ParentPosition, const float& ParentRotation, const Vector2& ParentScale, const float& ParentOpacity) override;
	virtual Vector2 GetSize(const Vector2& ParentScale) const override;

private:
	std::vector<std::shared_ptr<class Slot>> ChildSlots;

	Vector4 ChildrenPadding;
};

