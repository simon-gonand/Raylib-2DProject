#include "ImageWidget.h"
#include <raymath.h>

ImageWidget::ImageWidget(const char* TexturePath, const Color& InImageColor, const Vector2& InImageSize,
	const Vector2& InPosition, float InRotation, const Vector2& InScale, float InOpacity, const Vector4& InChildPadding, bool bInChildOverrideMinSize)
	: OneChildWidget(InPosition, InRotation, InScale, InOpacity, InChildPadding, bInChildOverrideMinSize), ImageColor{InImageColor}, ImageSize{InImageSize}
{
	SetImageTexture(TexturePath);
}

void ImageWidget::SetImageTexture(const char* TexturePath)
{
	ImageTexture = LoadTexture(TexturePath);
	if (ImageTexture.height > 0.0f && ImageTexture.width > 0.0f)
		ImageSize = { (float)ImageTexture.width, (float)ImageTexture.height };
}

void ImageWidget::SetImageTexture(const Texture2D& InImageTexture)
{
	ImageTexture = InImageTexture;
	if (ImageTexture.height > 0.0f && ImageTexture.width > 0.0f)
		ImageSize = { (float)ImageTexture.width, (float)ImageTexture.height };
}

void ImageWidget::SetImageColor(const Color& InImageColor)
{
	ImageColor = InImageColor;
}

void ImageWidget::Update(float DeltaTime, const Vector2& ParentPosition, const float& ParentRotation, const Vector2& ParentScale, const float& ParentOpacity)
{
	if (ImageTexture.height > 0.0f && ImageTexture.width > 0.0f)
		DrawTexture(ParentPosition, ParentRotation, ParentScale, ParentOpacity);
	else
		DrawRectangle(ParentPosition, ParentRotation, ParentScale, ParentOpacity);

	OneChildWidget::Update(DeltaTime, ParentPosition, ParentRotation, ParentScale, ParentOpacity);
}

Vector2 ImageWidget::GetSize(const Vector2& ParentScale) const
{
	Vector2 WorldScale = GetWorldScale(ParentScale);
	Vector2 Size = OneChildWidget::GetSize(ParentScale);
	
	if (!bChildOverrideMinSize) 
	{
		if (Size.x < ImageSize.x)
			Size.x = ImageSize.x;
		if (Size.y < ImageSize.y)
			Size.y = ImageSize.y;
	}

	return Vector2Multiply(Size, WorldScale);
}

void ImageWidget::DrawTexture(const Vector2& ParentPosition, const float& ParentRotation, const Vector2& ParentScale, const float& ParentOpacity)
{
	Vector2 WorldPosition = GetWorldPosition(ParentPosition);
	float WorldRotation = GetWorldRotation(ParentRotation);
	float WorldOpacity = GetWorldOpacity(ParentOpacity);

	Vector2 Size = GetSize(ParentScale);

	Rectangle Source =
	{
		0.0f,
		0.0f,
		ImageTexture.width,
		ImageTexture.height
	};

	Rectangle Destination =
	{
		WorldPosition.x,
		WorldPosition.y,
		Size.x,
		Size.y
	};

	DrawTexturePro(ImageTexture, Source, Destination, { 0.0f, 0.0f }, WorldRotation, Fade(ImageColor, WorldOpacity));
}

void ImageWidget::DrawRectangle(const Vector2& ParentPosition, const float& ParentRotation, const Vector2& ParentScale, const float& ParentOpacity)
{
	Vector2 WorldPosition = GetWorldPosition(ParentPosition);
	float WorldRotation = GetWorldRotation(ParentRotation);
	Vector2 WorldScale = GetWorldScale(ParentScale);
	float WorldOpacity = GetWorldOpacity(ParentOpacity);

	Vector2 Size = GetSize(WorldScale);

	Rectangle Rec =
	{
		WorldPosition.x,
		WorldPosition.y,
		Size.x * WorldScale.x,
		Size.y * WorldScale.y
	};

	DrawRectanglePro(Rec, {0.0f, 0.0f}, WorldRotation, GetDrawColorOpacity(ImageColor, WorldOpacity));
}
