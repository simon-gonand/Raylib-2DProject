#include "TextsWithBackgroundUserWidget.h"
#include "../../../Widgets/Text/TextWidget.h"

TextsWithBackgroundUserWidget::TextsWithBackgroundUserWidget(const char* InBackgroundTexturePath, std::vector<const char*> InTexts, bool bInTextOverrideBackgroundSize, Color TextsColor, Color DefaultBackgroundColor, const Vector2& InPosition, float InRotation, const Vector2& InScale, float InOpacity, const Vector4& InImagePadding, const Vector4& InTextsPadding)
	: UserWidget(InPosition, InRotation, InScale, InOpacity)
{
	BackgroundImageWidget = std::make_shared<ImageWidget>(InBackgroundTexturePath, Fade(DefaultBackgroundColor, 0.75f), Vector2({ 50.0f, 50.0f }), Vector2({ 0.0f }), 0.0f, Vector2({ 1.0f, 1.0f }), 0.75f, InImagePadding, bInTextOverrideBackgroundSize);
	RootWidget = BackgroundImageWidget;

	TextVerticalBox = std::make_shared<VerticalBox>(Vector2{0.0f}, 0.0f, Vector2{1.0f, 1.0f}, 1.0f, InTextsPadding);

	BackgroundImageWidget->SetChild(TextVerticalBox);
	for (const char* Text : InTexts)
	{
		if (Text != "")
		{
			TextVerticalBox->AddChild(std::make_shared<TextWidget>(Text, GetFontDefault(), 10.0f, 1.0f, TextsColor));
		}
	}
}

void TextsWithBackgroundUserWidget::EditTextAtIndex(int Index, const char* NewText)
{
	if (Index < 0)
		return;

	std::shared_ptr<TextWidget> ChildTextWidget = std::dynamic_pointer_cast<TextWidget>(TextVerticalBox->GetChildAt(Index));
	if (ChildTextWidget) 
	{
		ChildTextWidget->SetText(NewText);
	}
	else
	{
		TextVerticalBox->AddChild(std::make_shared<TextWidget>(NewText, GetFontDefault(), 10.0f));
	}
}

void TextsWithBackgroundUserWidget::Update(float DeltaTime)
{
	UserWidget::Update(DeltaTime);
}
