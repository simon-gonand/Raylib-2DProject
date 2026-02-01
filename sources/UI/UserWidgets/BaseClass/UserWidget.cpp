#include "UserWidget.h"

UserWidget::UserWidget(const Vector2& InPosition, float InRotation, const Vector2& InScale, float InOpacity)
	: Position{InPosition}, Rotation{InRotation}, Scale{InScale}, Opacity{InOpacity}
{
}

void UserWidget::Update(float DeltaTime)
{
	if (!RootWidget)
		return;

	RootWidget->Update(DeltaTime, Position, Rotation, Scale, Opacity);
}

void UserWidget::SetPosition(const Vector2& NewPosition)
{
	Position = NewPosition;
}
