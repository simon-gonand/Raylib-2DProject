#include "TextsWithBackgroundUserWidget.h"
#include "../../../Widgets/Text/TextWidget.h"

TextsWithBackgroundUserWidget::TextsWithBackgroundUserWidget(const char* InBackgroundTexturePath, std::vector<const char*> InTexts, bool bInTextOverrideBackgroundSize, const Vector2& InPosition, float InRotation, const Vector2& InScale, float InOpacity, const Vector4& InImagePadding, const Vector4& InTextsPadding)
	: UserWidget(InPosition, InRotation, InScale, InOpacity)
{
	BackgroundImageWidget = std::make_shared<ImageWidget>(InBackgroundTexturePath, Fade(WHITE, 0.75f), Vector2({ 50.0f, 50.0f }), Vector2({ 0.0f }), 0.0f, Vector2({ 1.0f, 1.0f }), 0.75f, InImagePadding, bInTextOverrideBackgroundSize);
	RootWidget = BackgroundImageWidget;

	TextVerticalBox = std::make_shared<VerticalBox>(Vector2{0.0f}, 0.0f, Vector2{1.0f, 1.0f}, 1.0f, InTextsPadding);

	BackgroundImageWidget->SetChild(TextVerticalBox);
	for (const char* Text : InTexts)
	{
		if (Text != "")
		{
			TextVerticalBox->AddChild(std::make_shared<TextWidget>(Text, GetFontDefault(), 10.0f));
		}
	}
}

void TextsWithBackgroundUserWidget::Update(float DeltaTime)
{
	UserWidget::Update(DeltaTime);
}
