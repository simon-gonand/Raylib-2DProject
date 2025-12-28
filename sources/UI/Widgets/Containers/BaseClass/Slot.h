#pragma once

#include <memory>

#include "../../BaseClass/Widget.h"

class Slot : public std::enable_shared_from_this<Slot>
{
public:
	Slot(Vector4 InPadding);

	virtual void Update(float DeltaTime, const Vector2& ParentPosition, const float& ParentRotation, const Vector2& ParentScale, const float& ParentOpacity);

	void SetPadding(const Vector4& InPadding);
	void SetWidgetRef(std::shared_ptr<Widget> InWidgetRef);

	virtual Vector2 UpdatePosition(const Vector2& InWidgetPosition) const;
	virtual Vector2 GetSize(const Vector2& ParentScale) const;

	const std::shared_ptr<Widget> GetWidgetRef() const;

protected:
	virtual Vector2 UpdateSize(const Vector2& InWidgetSize) const;

private:
	std::shared_ptr<Widget> WidgetRef;

	Vector4 Padding;
};

