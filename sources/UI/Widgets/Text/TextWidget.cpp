#include "TextWidget.h"

TextWidget::TextWidget(const char* InText, const Font& InTextFont, float InFontSize, float InSpacing, const Color& InTextColor,
	const Vector2& InPosition, float InRotation, const Vector2& InScale, float InOpacity)
	: Widget(InPosition, InRotation, InScale, InOpacity), Text{InText}, TextFont{InTextFont}, FontSize{InFontSize}, Spacing{InSpacing}, TextColor{InTextColor}
{
}

void TextWidget::SetText(const char* InText)
{
	Text = InText;
}

void TextWidget::SetTextFont(const Font& InTextFont)
{
	TextFont = InTextFont;
}

void TextWidget::SetFontSize(float InFontSize)
{
	FontSize = InFontSize;
}

void TextWidget::SetSpacing(float InSpacing)
{
	Spacing = InSpacing;
}

void TextWidget::SetTextColor(const Color& InTextColor)
{
	TextColor = InTextColor;
}

void TextWidget::Update(float DeltaTime, const Vector2& ParentPosition, const float& ParentRotation, const Vector2& ParentScale, const float& ParentOpacity)
{
	Vector2 WorldPosition = GetWorldPosition(ParentPosition);
	float WorldRotation = GetWorldRotation(ParentRotation);
	Vector2 WorldScale = GetWorldScale(ParentScale);
	float WorldOpacity = GetWorldOpacity(ParentOpacity);

	DrawTextPro(TextFont, Text, WorldPosition, {0.0f, 0.0f}, WorldRotation, FontSize * WorldScale.x, Spacing, GetDrawColorOpacity(TextColor, WorldOpacity));
}

Vector2 TextWidget::GetSize(const Vector2& ParentScale) const
{
	Vector2 WorldScale = GetWorldScale(ParentScale);
	return MeasureTextEx(TextFont, Text, FontSize * WorldScale.x, Spacing);
}
