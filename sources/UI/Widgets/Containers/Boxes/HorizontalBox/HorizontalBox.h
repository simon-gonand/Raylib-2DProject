#pragma once

#include "../../BaseClass/MultipleChildrenWidget.h"

class HorizontalBox : public MultipleChildrenWidget
{
public:
	HorizontalBox(const Vector2& InPosition = { 0.0f }, float InRotation = 0.0f, const Vector2& InScale = { 1.0f, 1.0f }, float InOpacity = 1.0f, const Vector4& InChildrenPadding = { 0.0f });

protected:
	virtual void Update(float DeltaTime, const Vector2& ParentPosition, const float& ParentRotation, const Vector2& ParentScale, const float& ParentOpacity) override;
	virtual Vector2 GetSize(const Vector2& ParentScale) const override;
};

