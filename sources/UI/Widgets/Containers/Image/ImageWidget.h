#pragma once

#include "../BaseClass/OneChildWidget.h"

class ImageWidget : public OneChildWidget
{
public:
	ImageWidget(const char* TexturePath, const Color& InImageColor, const Vector2& InImageSize = { 1.0f, 1.0f }, 
		const Vector2 & InPosition = { 0.0f }, float InRotation = 0.0f, const Vector2 & InScale = { 1.0f, 1.0f }, float InOpacity = 1.0f, bool bInChildOverrideMinSize = false);

	void SetImageTexture(const char* TexturePath);
	void SetImageTexture(const Texture2D& InImageTexture);
	void SetImageColor(const Color& InImageColor);

protected:
	virtual void Update(float DeltaTime, const Vector2& ParentPosition, const float& ParentRotation, const Vector2& ParentScale, const float& ParentOpacity) override;

	virtual Vector2 GetSize(const Vector2& ParentScale) const override;

private:
	Texture2D ImageTexture;
	Vector2 ImageSize;
	Color ImageColor;

	void DrawTexture(const Vector2& ParentPosition, const float& ParentRotation, const Vector2& ParentScale, const float& ParentOpacity);
	void DrawRectangle(const Vector2& ParentPosition, const float& ParentRotation, const Vector2& ParentScale, const float& ParentOpacity);
};

