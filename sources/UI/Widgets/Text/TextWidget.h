#pragma once

#include "../BaseClass/Widget.h"

#include <memory>

class TextWidget : public Widget
{
public:
	TextWidget(const char* InText, const Font& InTextFont = GetFontDefault(), float InFontSize = 5.0f, float InSpacing = 1.0f, 
		const Color& InTextColor = WHITE, const Vector2 & InPosition = { 0.0f }, float InRotation = 0.0f, const Vector2 & InScale = { 1.0f, 1.0f },
		float InOpacity = 1.0f);

	void SetText(const char* InText);
	void SetTextFont(const Font& InTextFont);
	void SetFontSize(float InFontSize);
	void SetSpacing(float InSpacing);
	void SetTextColor(const Color& InTextColor);

protected:
	virtual void Update(float DeltaTime, const Vector2& ParentPosition, const float& ParentRotation, const Vector2& ParentScale, const float& ParentOpacity) override;

	virtual Vector2 GetSize(const Vector2& ParentScale) const override;

private:
	const char* Text;
	Font TextFont;
	float FontSize;
	float Spacing;
	Color TextColor;
};

