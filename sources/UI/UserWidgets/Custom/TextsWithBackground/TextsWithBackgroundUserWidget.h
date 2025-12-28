#pragma once

#include "../../BaseClass/UserWidget.h"

#include "../../../Widgets/Containers/Image/ImageWidget.h"

#include <vector>

class TextsWithBackgroundUserWidget : public UserWidget
{
public:
	TextsWithBackgroundUserWidget(const char* InBackgroundTexturePath, const char* InTexts, bool bInTextOverrideBackgroundSize,
		const Vector2& InPosition = { 0.0f }, float InRotation = 0.0f, const Vector2& InScale = {1.0f, 1.0f}, float Opacity = 1.0f, const Vector4& InTextPadding = {0.0f});

	virtual void Initialize() override;

protected:
	virtual void Update(float DeltaTime) override;

private:
	const char* BackgroundTexturePath;
	const char* Texts;

	Vector4 TextPadding;

	bool bTextOverrideBackgroundSize;

	std::shared_ptr<ImageWidget> BackgroundImageWidget;
};

