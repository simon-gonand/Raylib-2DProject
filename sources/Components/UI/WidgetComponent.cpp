#include "WidgetComponent.h"

#include "../../UI/UserWidgets/BaseClass/UserWidget.h"
#include "../../Helpers/Math/Vectors/Vectors.h"

WidgetComponent::WidgetComponent(std::shared_ptr<class UserWidget> InUWidget, std::shared_ptr<Actor> InOwner, bool bAutoActivate,
	const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale) :
	TransformComponent(InOwner, bAutoActivate, InLocation, InRotation, InScale), UWidget{ InUWidget }
{
}

std::shared_ptr<UserWidget> WidgetComponent::GetWidget() const
{
	return UWidget;
}

void WidgetComponent::Update(float DeltaTime)
{
	if (UWidget)
	{
		UWidget->SetPosition(Vector::Vector3ToVector2(GetWorldLocation()));
		UWidget->Update(DeltaTime);
	}
}
