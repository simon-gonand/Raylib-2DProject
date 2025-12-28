#include "Widget.h"

#include <raymath.h>

Widget::Widget(const Vector2& InPosition, float InRotation, const Vector2& InScale, float InOpacity)
    : Position{InPosition}, Rotation{InRotation}, Scale{InScale}, Opacity{InOpacity}
{
}

Vector2 Widget::GetWorldPosition(const Vector2& ParentPosition) const
{
    return Vector2Add(ParentPosition, Position);
}

float Widget::GetWorldRotation(const float& ParentRotation) const
{
    return ParentRotation + Rotation;
}

Vector2 Widget::GetWorldScale(const Vector2& ParentScale) const
{
    return Vector2Multiply(ParentScale, Scale);
}

Color Widget::GetDrawColorOpacity(const Color& InColor, const float& InOpacity) const
{
    Color Result = InColor;
    float ColorOpacity = InColor.a / 255.0f;
    ColorOpacity *= InOpacity;
    Result = Fade(Result, ColorOpacity);
    return Result;
}

float Widget::GetWorldOpacity(const float& ParentOpacity) const
{
    return ParentOpacity * Opacity;
}
