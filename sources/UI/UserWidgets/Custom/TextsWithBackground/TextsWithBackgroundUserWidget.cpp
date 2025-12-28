#include "TextsWithBackgroundUserWidget.h"
#include "../../../Widgets/Text/TextWidget.h"

TextsWithBackgroundUserWidget::TextsWithBackgroundUserWidget(const char* InBackgroundTexturePath, const char* InTexts, bool bInTextOverrideBackgroundSize, const Vector2& InPosition, float InRotation, const Vector2& InScale, float InOpacity, const Vector4& InTextPadding)
	: UserWidget(InPosition, InRotation, InScale, InOpacity), BackgroundTexturePath{ InBackgroundTexturePath }, Texts{ InTexts }, bTextOverrideBackgroundSize{bInTextOverrideBackgroundSize}, TextPadding{ InTextPadding }
{
}

void TextsWithBackgroundUserWidget::Initialize()
{
	BackgroundImageWidget = std::make_shared<ImageWidget>(BackgroundTexturePath, Fade(WHITE, 0.75f), Vector2({ 50.0f, 50.0f }), Vector2({ 0.0f }), 0.0f, Vector2({ 1.0f, 1.0f }), 0.75f, TextPadding, bTextOverrideBackgroundSize);
	RootWidget = BackgroundImageWidget;

	BackgroundImageWidget->SetChild(std::make_shared<TextWidget>(Texts, GetFontDefault(), 10.0f, 1.0f, BLACK));
}

void TextsWithBackgroundUserWidget::Update(float DeltaTime)
{
	UserWidget::Update(DeltaTime);
}
