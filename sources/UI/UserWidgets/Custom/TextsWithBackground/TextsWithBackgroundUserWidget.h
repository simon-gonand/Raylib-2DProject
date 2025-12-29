#pragma once

#include "../../BaseClass/UserWidget.h"

#include "../../../Widgets/Containers/Image/ImageWidget.h"
#include "../../../Widgets/Containers/Boxes/VerticalBox/VerticalBox.h"

#include <vector>

class TextsWithBackgroundUserWidget : public UserWidget
{
public:
	TextsWithBackgroundUserWidget(const char* InBackgroundTexturePath, std::vector<const char*> InTexts, bool bInTextOverrideBackgroundSize,
		const Vector2& InPosition = { 0.0f }, float InRotation = 0.0f, const Vector2& InScale = {1.0f, 1.0f}, float Opacity = 1.0f, const Vector4& InImagePadding = { 0.0f }, const Vector4& InTextsPadding = {0.0f});

	void EditTextAtIndex(int Index, const char* NewText);

protected:
	virtual void Update(float DeltaTime) override;

private:
	std::shared_ptr<ImageWidget> BackgroundImageWidget;
	std::shared_ptr<VerticalBox> TextVerticalBox;
};

