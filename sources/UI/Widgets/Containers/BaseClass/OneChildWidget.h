#pragma once

#include "../../BaseClass/Widget.h"

#include <memory>

class OneChildWidget : public Widget
{
public:
	OneChildWidget(const Vector2& InPosition = { 0.0f }, float InRotation = 0.0f, const Vector2& InScale = { 1.0f, 1.0f }, float Opacity = 1.0f, const Vector4& ChildPadding = {0.0f}, bool bInChildOverrideMinSize = false);

	void SetChild(std::shared_ptr<Widget> InChild);

protected:
	bool bChildOverrideMinSize;

	virtual void Update(float DeltaTime, const Vector2& ParentPosition, const float& ParentRotation, const Vector2& ParentScale, const float& ParentOpacity) override;

	virtual Vector2 GetSize(const Vector2& ParentScale) const override;

private:
	std::shared_ptr<class Slot> ChildSlot;
};

