#pragma once

#include "../../Widgets/BaseClass/Widget.h"

#include <memory>
#include <raylib.h>

class UserWidget
{
public:
	UserWidget(const Vector2& InPosition = {0.0f}, float InRotation = 0.0f, const Vector2& InScale = { 1.0f, 1.0f }, float InOpacity = 1.0f);

	virtual void Update(float DeltaTime);

	void SetPosition(const Vector2& NewPosition);

protected:
	std::shared_ptr<Widget> RootWidget;

	Vector2 Position;
	float Rotation;
	Vector2 Scale;
	float Opacity;
};

